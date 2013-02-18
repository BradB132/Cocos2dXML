//
//  SpriteBatch.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "SpriteBatch.h"

void SpriteBatch::load()
{
	if(!node)
	{
		node = cocos2d::CCSpriteBatchNode::create(texture.c_str());
		node->retain();
	}
	
	if(plist != "")
		cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str());
	
	SpriteBatch_Base::load();
}