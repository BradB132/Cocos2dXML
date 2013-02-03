//
//  Script.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/1/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Script.h"
#include "cocos2d.h"

#pragma mark - Script memory cache

static std::map<std::string, RequiredScript> scriptCache;
static std::vector<Script*> scriptStack;

#pragma mark - NoPL callbacks

NoPL_FunctionValue evaluateFunction(void* calledOnObject, const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	Script* callingFromScript = scriptStack.at(scriptStack.size()-1);
	
	//check if this is a global
	if(!calledOnObject)
	{
		if(!strcmp(functionName, "scene") ||
		   !strcmp(functionName, "scope") )
		{
			//return the scope object that this script is in
			returnVal.pointerValue = callingFromScript->getRootObject();
			returnVal.type = NoPL_DataType_Pointer;
		}
	}
	else
	{
		//assume this object is the correct type for now (TODO: fix that)
		BaseObject_Base* obj = (BaseObject_Base*)calledOnObject;
		returnVal = obj->evaluateFunction(functionName, argv, argc);
	}
	
	return returnVal;
}

NoPL_FunctionValue evaluateSubscript(void* calledOnObject, NoPL_FunctionValue index)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	//TODO: finish this
	
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

void Script::load()
{
	script = Script::requireScriptAtPath(path);
	
	if(runListener == "")
		runTheScript();
}

void Script::unload()
{
	Script::relinquishScriptAtPath(path);
}

void Script::runTheScript()
{
	if(!script)
		return;
	
	scriptStack.push_back(this);
	runScript(script->scriptBuffer, (unsigned int)script->bufferLength, &scriptCallbacks);
	scriptStack.pop_back();
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
