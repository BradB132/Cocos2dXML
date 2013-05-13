//
//  Sprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Sprite.h"
#include "sprite_nodes/CCSprite.h"
#include "CCXMLSprite.h"

void Sprite::load()
{
	if(!node)
	{
		node = new CCXMLSprite();
		((cocos2d::CCSprite*)node)->init();
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
				//we're potentially going to be attempting to load files that don't exist, disable the popups
				bool usingMessageBox = cocos2d::CCFileUtils::sharedFileUtils()->isPopupNotify();
				cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(false);
				
				CCXMLSprite* sprite = (CCXMLSprite*)node;
				cocos2d::CCTexture2D* texture2d = NULL;
				
				//find the highest resolution version of the texture
				int contentScale = (int)cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
				int imageScale = contentScale;
				if(contentScale > 1)
				{
					char formatStr[texture.length()+5];
					int pathExtensionIndex = texture.rfind('.');
					const char* pathPrefix = texture.substr(0,pathExtensionIndex).c_str();
					const char* pathSuffix = texture.substr(pathExtensionIndex).c_str();
					while(imageScale > 1)
					{
						//format a @x suffix onto the file name
						sprintf(formatStr, "%s@%dx%s", pathPrefix, imageScale, pathSuffix);
						
						//check if we have this texture
						texture2d = cocos2d::CCTextureCache::sharedTextureCache()->addImage(formatStr);
						if(texture2d)
							break;
						
						imageScale--;
					}
				}
				
				//attempt to get the texture at 1x scale
				if(!texture2d)
					texture2d = cocos2d::CCTextureCache::sharedTextureCache()->addImage(texture.c_str());
				
				//restore previous message box state
				cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(usingMessageBox);
				
				if(texture2d)
				{
					sprite->setAssetScale(imageScale);
					cocos2d::CCSize texSize = texture2d->getContentSize();
					sprite->setDisplayFrame(cocos2d::CCSpriteFrame::createWithTexture(texture2d, cocos2d::CCRect(0,0,texSize.width,texSize.height)));
				}
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
