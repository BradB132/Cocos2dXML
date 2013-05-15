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

NoPL_FunctionValue Sprite::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue retVal;
	retVal.type = NoPL_DataType_Uninitialized;
	
	if(argc == 2 &&
	   argv[0].type == NoPL_DataType_Number &&
	   argv[1].type == NoPL_DataType_Number &&
	   !strcmp(functionName, "setTexCoordOffset"))
	{
		CCXMLSprite* sprite = (CCXMLSprite*)node;
		cocos2d::CCSize texSize = sprite->getTexture()->getContentSize();
		float scaleFactor = cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
		sprite->setTextureCoords(cocos2d::CCRect(argv[0].numberValue/scaleFactor, argv[1].numberValue/scaleFactor, texSize.width, texSize.height));
		retVal.type = NoPL_DataType_Void;
	}
	
	if(retVal.type != NoPL_DataType_Uninitialized)
		return retVal;
	return Sprite_Base::evaluateFunction(functionName, argv, argc);
}

cocos2d::ccTexParams Sprite::getTexParams()
{
	CCXMLSprite* sprite = (CCXMLSprite*)node;
	cocos2d::ccTexParams params;
	
	//with these filter settings, we're assuming we want antialiasing
	if(sprite && sprite->getTexture() && sprite->getTexture()->hasMipmaps())
		params.minFilter = GL_LINEAR_MIPMAP_NEAREST;
	else
		params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapS = params.wrapT = textureWrap;
	
	return params;
}

bool Sprite::setColor(Cocos2dXMLColor newColor)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		sprite->setColor(color.rgb);
		sprite->setOpacity(color.a);
	}
	return Sprite_Base::setColor(newColor);
}

bool Sprite::setTexture(Cocos2dXMLFilePath newTexture)
{
	if(node)
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
	return Sprite_Base::setTexture(newTexture);
}

bool Sprite::setFlipX(bool newFlipX)
{
	if(node)
		((cocos2d::CCSprite*)node)->setFlipX(newFlipX);
	return Sprite_Base::setFlipX(newFlipX);
}

bool Sprite::setFlipY(bool newFlipY)
{
	if(node)
		((cocos2d::CCSprite*)node)->setFlipX(newFlipY);
	return Sprite_Base::setFlipX(newFlipY);
}

bool Sprite::setSrcBlend(srcBlendFunc newSrcBlend)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		cocos2d::ccBlendFunc func = sprite->getBlendFunc();
		if(newSrcBlend == srcBlendFunc_default)
		{
			//we need some special logic here to mimic how cocos2d handles the blend state
			cocos2d::CCTexture2D* tex = sprite->getTexture();
			if (!tex || ! tex->hasPremultipliedAlpha())
				func.src = GL_SRC_ALPHA;
			else
				func.src = CC_BLEND_SRC;
		}
		else
			func.src = newSrcBlend;
		sprite->setBlendFunc(func);
	}
	return Sprite_Base::setSrcBlend(newSrcBlend);
}

bool Sprite::setDstBlend(dstBlendFunc newDstBlend)
{
	if(node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		cocos2d::ccBlendFunc func = sprite->getBlendFunc();
		func.dst = newDstBlend;
		sprite->setBlendFunc(func);
	}
	return Sprite_Base::setDstBlend(newDstBlend);
}

bool Sprite::setTextureWrap(textureWrapMode newTextureWrap)
{
	bool result = Sprite_Base::setTextureWrap(newTextureWrap);
	if(result && node)
	{
		cocos2d::CCSprite* sprite = (cocos2d::CCSprite*)node;
		cocos2d::ccTexParams params = getTexParams();
		sprite->getTexture()->setTexParameters(&params);
	}
	return result;
}
