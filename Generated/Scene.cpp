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

bool Scene::setOnUpdate(Cocos2dXMLEvent newOnUpdate)
{
	//remove self from scheduler
	cocos2d::CCScheduler* scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
	scheduler->unscheduleUpdateForTarget(this);
	
	//only re-schedule if we have an actual event name
	if(onUpdate != "")
		scheduler->scheduleUpdateForTarget(this, 0, false);
	
	return Scene_Base::setOnUpdate(newOnUpdate);
}

bool Scene::setPushSceneListener(Cocos2dXMLEventListener newPushSceneListener)
{
	listenForEvent(newPushSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePushEvent));
	return Scene_Base::setPushSceneListener(newPushSceneListener);
}

bool Scene::setSwapSceneListener(Cocos2dXMLEventListener newSwapSceneListener)
{
	listenForEvent(newSwapSceneListener, cocos2d::SEL_NoteHandler(&Scene::handleSwapEvent));
	return Scene_Base::setSwapSceneListener(newSwapSceneListener);
}

bool Scene::setPopSceneListener(Cocos2dXMLEventListener newPopSceneListener)
{
	listenForEvent(newPopSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePopEvent));
	return Scene_Base::setPopSceneListener(newPopSceneListener);
}

bool Scene::setPopToRootSceneListener(Cocos2dXMLEventListener newPopToRootSceneListener)
{
	listenForEvent(newPopToRootSceneListener, cocos2d::SEL_NoteHandler(&Scene::handlePopRootEvent));
	return Scene_Base::setPopToRootSceneListener(newPopToRootSceneListener);
}

bool Scene::setScale(cocos2d::CCPoint newScale)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setPosition(cocos2d::CCPoint newPosition)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setSkew(cocos2d::CCPoint newSkew)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setAnchorPoint(cocos2d::CCPoint newAnchorPoint)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setSize(cocos2d::CCPoint newSize)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setRotation(float newRotation)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
}

bool Scene::setIgnoreAnchorPointForPosition(bool newIgnoreAnchorPointForPosition)
{
	//ignore this attribute, it doesn't ever make sense to set it on a scene
	return false;
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
	//the setOnUpdate call already checks to make sure onUpdate has a real value
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
