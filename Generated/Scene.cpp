//
//  Scene.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Scene.h"
#include "Director.h"

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
	
	//remove self from scheduler
	cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
	
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
		case id_Node_scale:
		case id_Node_position:
		case id_Node_size:
		case id_Node_anchorPoint:
		case id_Node_skew:
		case id_Node_rotation:
		case id_Node_ignoreAnchorPointForPosition:
			//ignore these attributes, it doesn't ever make sense to set them on a scene
			return;
	}
	
	Scene_Base::attributeDidChange(attributeID);
}

void Scene::handlePopEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	Director::sharedDirector()->popScene();
}

void Scene::handlePopRootEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	Director::sharedDirector()->popToRootScene();
}

void getSceneAndTransitionParams(cocos2d::CCDictionary* params, SceneReference** outSceneRef, Transition** outTrans)
{
	//make sure that we at least return NULL instead of garbage values
	*outSceneRef = NULL;
	*outTrans = NULL;
	
	//make sure that we have the params that we need
	cocos2d::CCString* sceneRefId = (cocos2d::CCString*)params->objectForKey("scene");
	cocos2d::CCString* transitionId = (cocos2d::CCString*)params->objectForKey("transition");
	if(!sceneRefId)
		return;
	
	//get the scene reference and transition
	Director* xmlDirector = Director::sharedDirector();
	*outSceneRef = xmlDirector->sceneRefForID(sceneRefId->getCString());
	if(transitionId)
		*outTrans = xmlDirector->transitionForID(transitionId->getCString());
}

void Scene::handlePushEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	//get the scene ref and transition
	SceneReference* sceneRef;
	Transition* trans;
	getSceneAndTransitionParams(params, &sceneRef, &trans);
	
	//transition to the next scene
	Director::sharedDirector()->switchToScene(sceneRef, trans, true);
}

void Scene::handleSwapEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	//get the scene ref and transition
	SceneReference* sceneRef;
	Transition* trans;
	getSceneAndTransitionParams(params, &sceneRef, &trans);
	
	//transition to the next scene
	Director::sharedDirector()->switchToScene(sceneRef, trans, false);
}

void Scene::update(float dt)
{
	//the attributeDidChange call already checks to make sure onUpdate has a real value
	if(!((cocos2d::CCScene*)node)->isTransitioning())
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
