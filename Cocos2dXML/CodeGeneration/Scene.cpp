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
