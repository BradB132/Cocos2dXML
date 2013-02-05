//
//  BaseObject.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "BaseObject.h"
#include "Scene.h"

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

void BaseObject::postEvent(std::string eventName)
{
	cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
	center->postNotification(eventName.c_str(), getRootObject());
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
	if(getId() == "")
		return;
	
	//attempt to remove self from scene
	BaseObject* rootObj = getRootObject();
	Scene* rootScene = dynamic_cast<Scene*>(rootObj);
	if(rootScene)
	{
		rootScene->removeFromSceneMap(this);
	}
	
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
