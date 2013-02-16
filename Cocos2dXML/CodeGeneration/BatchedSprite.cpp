//
//  BatchedSprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "BatchedSprite.h"

void BatchedSprite::load()
{
	if(!node)
	{
		node = cocos2d::CCSprite::createWithSpriteFrameName(texture.c_str());
		node->retain();
	}
	
	BatchedSprite_Base::load();
}

void BatchedSprite::attributeDidChange(int attributeID)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		switch (attributeID)
		{
			case id_BatchedSprite_color:
				sprite->setColor(color.rgb);
				sprite->setOpacity(color.a);
				return;
			case id_BatchedSprite_texture:
			{
				cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture.c_str());
				sprite->setDisplayFrame(frame);
				
				//we generally also want this node to be the same size as the image
				cocos2d::CCSize newSize = frame->getRect().size;
				this->setSize(cocos2d::CCPoint(newSize.width, newSize.height));
			}
				return;
			case id_BatchedSprite_flipX:
				sprite->setFlipX(flipX);
				return;
			case id_BatchedSprite_flipY:
				sprite->setFlipY(flipY);
				return;
			case id_BatchedSprite_srcBlend:
			case id_BatchedSprite_dstBlend:
			{
//TODO: fix this
//				cocos2d::ccBlendFunc func;
//				func.src = srcBlend;
//				func.dst = dstBlend;
//				sprite->setBlendFunc(func);
			}
				return;
		}
	}
	BatchedSprite_Base::attributeDidChange(attributeID);
}
