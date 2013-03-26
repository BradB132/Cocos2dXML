//
//  BaseObject.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "BaseObject.h"
#include "Scene.h"

#define kEventParamDelimiter ','
#define kEventParamKeyValuePairing '='
#define kEventParamStartChar '('
#define kEventParamEndChar ')'

BaseObject::BaseObject():
alreadySetID(false)
{
}

BaseObject* BaseObject::getRootObject()
{
	//traverse our way up the hierarchy until we have no parent
	if(parent)
		return ((BaseObject*)parent)->getRootObject();
	return this;
}

BaseObject* BaseObject::objectForID(std::string objectID)
{
	//attempt to get the parent scene
	BaseObject* rootObj = getRootObject();
	Scene* rootScene = dynamic_cast<Scene*>(rootObj);
	if(rootScene)
	{
		return rootScene->objectFromMap(objectID);
	}
	return NULL;
}

void trimString(std::string* s)
{
	s->erase(s->begin(), std::find_if(s->begin(), s->end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	s->erase(std::find_if(s->rbegin(), s->rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s->end());
}

void BaseObject::postEvent(std::string eventName, cocos2d::CCDictionary* args)
{
	//check if this string has inline parameters, ex: eventName(paramName=paramValue)
	if(eventName[eventName.length()-1] == kEventParamEndChar)
	{
		int index = eventName.rfind(kEventParamStartChar);
		if(index != std::string::npos)
		{
			//we are now sure that there are inlined args, make sure we have a dictionary to put them in
			if(!args)
				args = cocos2d::CCDictionary::create();
			
			//get substrings that represent the params and the event name
			std::string paramsStr = eventName.substr(index+1, (eventName.length()-index)-2);
			eventName = eventName.substr(0,index);
			
			//iterate over all of the delimited params
			int delimitIndex = 0;
			while(true)
			{
				//get the next expression in the sequence
				int nextIndex = paramsStr.find(kEventParamDelimiter, delimitIndex);
				bool shouldBreak = (nextIndex == std::string::npos);
				std::string keyValuePair;
				if(shouldBreak)
					keyValuePair = paramsStr.substr(delimitIndex);
				else
					keyValuePair = paramsStr.substr(delimitIndex, nextIndex-delimitIndex);
				
				//split the key and the value
				int keyValueSplit = keyValuePair.find(kEventParamKeyValuePairing);
				if(keyValueSplit != std::string::npos)
				{
					std::string keyString = keyValuePair.substr(0,keyValueSplit);
					std::string valString = keyValuePair.substr(keyValueSplit+1);
					trimString(&keyString);
					trimString(&valString);
					
					//add this key to the parameters
					args->setObject(cocos2d::CCString::create(valString), keyString);
				}
				
				if(shouldBreak)
					break;
				
				delimitIndex = nextIndex+1;
			}
		}
	}
	
	cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
	center->postNotification(eventName.c_str(), args, getRootObject());
}

void BaseObject::postEvent(std::string eventName)
{
	postEvent(eventName, NULL);
}

void BaseObject::listenForEvent(std::string eventName, cocos2d::SEL_NoteHandler selector)
{
	//listen to the new notification
	cocos2d::CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
																		   selector,
																		   eventName.c_str(),
																		   getRootObject());
}

void BaseObject::stopListeningToEvent(std::string eventName)
{
	cocos2d::CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, eventName.c_str());
}

void BaseObject::stopListeningToAllEvents()
{
	cocos2d::CCNotificationCenter::sharedNotificationCenter()->removeObserver(this);
}

void BaseObject::load()
{
	//attempt to add self to scene
	BaseObject* rootObj = getRootObject();
	Scene* rootScene = dynamic_cast<Scene*>(rootObj);
	if(rootScene)
	{
		rootScene->addToSceneMap(this);
	}
	
	BaseObject_Base::load();
}

void BaseObject::unload()
{
	if(getId() != "")
	{
		//attempt to remove self from scene
		BaseObject* rootObj = getRootObject();
		Scene* rootScene = dynamic_cast<Scene*>(rootObj);
		if(rootScene)
		{
			rootScene->removeFromSceneMap(this);
		}
	}
	
	stopListeningToAllEvents();
	
	BaseObject_Base::unload();
}

bool BaseObject::setId(std::string newId)
{
	//the ID should only ever be set once (during XML parsing)
	if(!alreadySetID)
	{
		alreadySetID = true;
		return BaseObject_Base::setId(newId);
	}
	return false;
}
