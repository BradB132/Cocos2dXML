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
