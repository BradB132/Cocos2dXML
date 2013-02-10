//
//  Sprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Sprite.h"
#include "sprite_nodes/CCSprite.h"

void Sprite::formatTexturePathWithSuffix()
{
	//cocos no longer supports content scale suffix, so we'll have to do that ourselves
	int scaleSufix = (int)cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
	if(scaleSufix == 1)
		pathWithResolutionSuffix = texture;
	else
	{
		while (scaleSufix > 1)
		{
			//add a @x suffix onto the file name
			char formatStr[texture.length()+5];
			int index = texture.rfind('.');
			sprintf(formatStr, "%s@%dx%s", texture.substr(0,index).c_str(), scaleSufix, texture.substr(index).c_str());
			pathWithResolutionSuffix = formatStr;
			
			//TODO: check if file exists, then break if it does
			break;
			
			scaleSufix--;
		}
	}
}

void Sprite::load()
{
	if(!node)
	{
		formatTexturePathWithSuffix();
		node = cocos2d::CCSprite::create(pathWithResolutionSuffix.c_str());
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
				formatTexturePathWithSuffix();
				
				cocos2d::CCTexture2D* tex = cocos2d::CCTextureCache::sharedTextureCache()->addImage(pathWithResolutionSuffix.c_str());
				sprite->setTexture(tex);
				
				//we generally also want this node to be the same size as the image
				this->setSize(cocos2d::CCPoint(tex->getContentSize().width, tex->getContentSize().height));
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
