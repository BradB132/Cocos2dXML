//
//  Scene.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Scene.h"

void Scene::load()
{
	if(!node)
	{
		node = cocos2d::CCScene::create();
		node->retain();
	}
	
	Scene_Base::load();
}

void Scene::unload()
{
	//dump anything that was in our mapping
	objectMap.clear();
	
	Scene_Base::unload();
}

void Scene::visitLoad()
{
	Scene_Base::visitLoad();
	
	//do this after the visit to make sure everything in the scene is ready to go
	if(onLoad != "")
		postEvent(onLoad);
}

void Scene::attributeDidChange(int attributeID)
{
	switch (attributeID)
	{
		case id_Scene_onUpdate:
		{
			//remove self from scheduler
			cocos2d::CCScheduler* scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
			scheduler->unscheduleUpdateForTarget(this);
			
			//only re-schedule if we have an actual event name
			if(onUpdate != "")
				scheduler->scheduleUpdateForTarget(this, 0, false);
		}
			return;
		case id_Scene_popSceneListener:
		{
			listenForEvent(popSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePopEvent));
		}
			return;
		case id_Scene_popToRootSceneListener:
		{
			listenForEvent(popToRootSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePopRootEvent));
		}
			return;
		case id_Scene_pushSceneListener:
		{
			listenForEvent(pushSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePushEvent));
		}
			return;
		case id_Scene_swapSceneListener:
		{
			listenForEvent(swapSceneListener, cocos2d::SEL_NoteHandler(&Scene::handleSwapEvent));
		}
			return;
	}
	
	Scene_Base::attributeDidChange(attributeID);
}

void Scene::handlePopEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	cocos2d::CCDirector::sharedDirector()->popScene();
}

void Scene::handlePopRootEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	cocos2d::CCDirector::sharedDirector()->popToRootScene();
}

void Scene::handlePushEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	
}

void Scene::handleSwapEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	
}

void Scene::update(float dt)
{
	//the attributeDidChange call already checks to make sure onUpdate has a real value
	postEvent(onUpdate);
}

void Scene::addToSceneMap(BaseObject* obj)
{
	objectMap[obj->getId()] = obj;
}

void Scene::removeFromSceneMap(BaseObject* obj)
{
	objectMap.erase(obj->getId());
}

BaseObject* Scene::objectFromMap(std::string objectID)
{
	if(objectMap.find(objectID) != objectMap.end())
		return objectMap[objectID];
	return NULL;
}

NoPL_FunctionValue Scene::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue retVal;
	retVal.type = NoPL_DataType_Uninitialized;
	
	//check for a matching ID in this scene
	BaseObject* matchingObject = objectFromMap(functionName);
	if(matchingObject)
	{
		retVal.pointerValue = matchingObject;
		retVal.type = NoPL_DataType_Pointer;
	}
	
	//return the result if we found one
	if(retVal.type != NoPL_DataType_Uninitialized)
		return retVal;
	return Node::evaluateFunction(functionName, argv, argc);
}
