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