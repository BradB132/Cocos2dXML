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

void Sprite::refreshAttribute(int attributeID)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = dynamic_cast<cocos2d::CCSprite*>(node);
		if(sprite)
		{
			switch (attributeID)
			{
				case refresh_Sprite_color:
					sprite->setColor(color.rgb);
					sprite->setOpacity(color.a);
					return;
				case refresh_Sprite_texture:
				{
					cocos2d::CCTexture2D* tex = cocos2d::CCTextureCache::sharedTextureCache()->addImage(texture.c_str());
					sprite->setTexture(tex);
					
					//we generally also want this node to be the same size as the image
					sprite->setContentSize(tex->getContentSize());
				}
					return;
				case refresh_Sprite_flipX:
					sprite->setFlipX(flipX);
					return;
				case refresh_Sprite_flipY:
					sprite->setFlipY(flipY);
					return;
				case refresh_Sprite_srcBlend:
					//TODO: update blend
					return;
				case refresh_Sprite_dstBlend:
					//TODO: update blend
					return;
			}
		}
	}
	Sprite_Base::refreshAttribute(attributeID);
}
