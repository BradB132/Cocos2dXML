//
//  CCXMLSprite.cpp
//  Cocos2dXML
//
//  Created by Brad Bambara on 5/9/13.
//  Copyright (c) 2013 Robox Studios. All rights reserved.
//

#include "CCXMLSprite.h"
#include "CCDirector.h"

CCXMLSprite::CCXMLSprite():
assetScale(1.0f)
{
}

void CCXMLSprite::setTextureCoords(const cocos2d::CCRect& rect)
{
	CCSprite::setTextureCoords(rect);
}

void CCXMLSprite::setVertexRect(const cocos2d::CCRect& rect)
{
	m_obRect = rect;
	float rectScale = ((int)cocos2d::CCDirector::sharedDirector()->getContentScaleFactor())/assetScale;
	m_obRect.size.width *= rectScale;
	m_obRect.size.height *= rectScale;
	setContentSize(m_obRect.size);
}

void CCXMLSprite::setAssetScale(float scale)
{
	assetScale = scale;
}

float CCXMLSprite::getAssetScale()
{
	return assetScale;
}
