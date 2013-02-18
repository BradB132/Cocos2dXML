//
//  Script.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/1/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Script.h"
#include "cocos2d.h"
#include "NoPLStandardFunctions.h"

#pragma mark - Script memory cache

static std::map<std::string, RequiredScript> scriptCache;
static std::vector<Script*> scriptStack;

#pragma mark - NoPL callbacks

NoPL_FunctionValue evaluateFunction(void* calledOnObject, const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	//check if this is a global
	if(!calledOnObject)
	{
		Script* callingFromScript = scriptStack.at(scriptStack.size()-1);
		
		if(!strcmp(functionName, "scene") ||
		   !strcmp(functionName, "scope") )
		{
			//return the scope object that this script is in
			returnVal.pointerValue = callingFromScript->getRootObject();
			returnVal.type = NoPL_DataType_Pointer;
		}
		else if(!strcmp(functionName, "args") ||
				!strcmp(functionName, "arguments") )
		{
			returnVal.pointerValue = callingFromScript->getCurrentParams();
			returnVal.type = NoPL_DataType_Pointer;
		}
		else if(!strcmp(functionName, "director"))
		{
			returnVal.pointerValue = cocos2d::CCDirector::sharedDirector();
			returnVal.type = NoPL_DataType_Pointer;
		}
		
		if(returnVal.type == NoPL_DataType_Uninitialized)
			returnVal = nopl_standardFunctions(calledOnObject, functionName, argv, argc);
	}
	else
	{
		//it should be safe to assume all pointers are CCObjects
		cocos2d::CCObject* obj = (cocos2d::CCObject*)calledOnObject;
		returnVal = obj->evaluateFunction(functionName, argv, argc);
	}
	
	return returnVal;
}

NoPL_FunctionValue evaluateSubscript(void* calledOnObject, NoPL_FunctionValue index)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	if(calledOnObject)
	{
		//it should be safe to assume all pointers are CCObjects
		cocos2d::CCObject* obj = (cocos2d::CCObject*)calledOnObject;
		returnVal = obj->evaluateSubscript(index);
	}
	
	return returnVal;
}

void stringFeedback(const char* string, NoPL_StringFeedbackType type)
{
	if(type == NoPL_StringFeedbackType_PrintStatement)
	{
		printf("Script: %s\n", string);
	}
}

static NoPL_Callbacks scriptCallbacks = {evaluateFunction, evaluateSubscript, stringFeedback};

#pragma mark - Script

Script::Script():
currentParams(NULL)
{
}

void Script::load()
{
	refreshAllAttributes();
	script = Script::requireScriptAtPath(path);
	
	if(runListener == "")
		runTheScript();
}

void Script::unload()
{
	cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
	center->removeObserver(this);
	
	Script::relinquishScriptAtPath(path);
}

void Script::attributeDidChange(int attributeID)
{
	switch (attributeID)
	{
		case id_Script_runListener:
		{
			cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
		
			//remove self from any notifications
			center->removeObserver(this);
			
			//listen to the new notification
			center->addObserver(this,
								cocos2d::SEL_NoteHandler(&Script::handleRunEvent),
								runListener.c_str(),
								getRootObject());
		}
			return;
	}
	Script_Base::attributeDidChange(attributeID);
}

void Script::handleRunEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	currentParams = params;
	runTheScript();
	currentParams = NULL;
}

void Script::runTheScript()
{
	if(!script)
		return;
	
	scriptStack.push_back(this);
	runScript(script->scriptBuffer, (unsigned int)script->bufferLength, &scriptCallbacks);
	scriptStack.pop_back();
}

cocos2d::CCDictionary* Script::getCurrentParams()
{
	return currentParams;
}

const RequiredScript* Script::requireScriptAtPath(std::string path)
{
	RequiredScript* scriptPtr = NULL;
	
	//check if our memory cache already has the script
	if(scriptCache.find(path) != scriptCache.end())
	{
		//we already have this script loaded
		scriptPtr = &(scriptCache[path]);
		scriptPtr->requireCount++;
	}
	else
	{
		//we didn't have this script yet, load it from file
		RequiredScript newScript;
		newScript.scriptBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &(newScript.bufferLength));
		newScript.requireCount = 1;
		
		//check to make sure the load was a success
		if(newScript.scriptBuffer)
		{
			scriptCache[path] = newScript;
			scriptPtr = &(scriptCache[path]);
		}
	}
	
	return scriptPtr;
}

void Script::relinquishScriptAtPath(std::string path)
{
	//sanity check to make sure we actually have this script in the cache
	if(scriptCache.find(path) != scriptCache.end())
	{
		//decrement the require count on this script
		RequiredScript* scriptPtr = &(scriptCache[path]);
		scriptPtr->requireCount--;
		
		//do we need this script anymore?
		if(scriptPtr->requireCount <= 0)
		{
			//delete the buffer
			if(scriptPtr->scriptBuffer)
			{
				delete[] scriptPtr->scriptBuffer;
				scriptPtr = NULL;
			}
			scriptPtr->bufferLength = 0;
			
			//remove from the cache
			scriptCache.erase(path);
		}
	}
}
