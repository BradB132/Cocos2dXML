//
//  Sprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Sprite.h"
#include "sprite_nodes/CCSprite.h"

void Sprite::load()
{
	if(!node)
	{
		node = cocos2d::CCSprite::create(texture.c_str());
		node->retain();
	}
	
	Sprite_Base::load();
}

void Sprite::attributeDidChange(int attributeID)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		switch (attributeID)
		{
			case id_Sprite_color:
				sprite->setColor(color.rgb);
				sprite->setOpacity(color.a);
				return;
			case id_Sprite_texture:
			{
				cocos2d::CCTexture2D* tex = cocos2d::CCTextureCache::sharedTextureCache()->addImage(texture.c_str());
				sprite->setTexture(tex);
				
				//we generally also want this node to be the same size as the image
				sprite->setContentSize(tex->getContentSize());
			}
				return;
			case id_Sprite_flipX:
				sprite->setFlipX(flipX);
				return;
			case id_Sprite_flipY:
				sprite->setFlipY(flipY);
				return;
			case id_Sprite_srcBlend:
			case id_Sprite_dstBlend:
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
	Sprite_Base::attributeDidChange(attributeID);
}
