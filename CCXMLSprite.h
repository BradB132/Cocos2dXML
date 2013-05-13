//
//  CCXMLSprite.h
//  Cocos2dXML
//
//  Created by Brad Bambara on 5/9/13.
//  Copyright (c) 2013 Robox Studios. All rights reserved.
//

#ifndef __Cocos2dXML__CCXMLSprite__
#define __Cocos2dXML__CCXMLSprite__

#include "sprite_nodes/CCSprite.h"

class CCXMLSprite : public cocos2d::CCSprite
{
public:
	
	CCXMLSprite();
	
	virtual void setTextureCoords(const cocos2d::CCRect& rect);
	virtual void setVertexRect(const cocos2d::CCRect& rect);
	
	void setAssetScale(float scale);
	float getAssetScale();
	
protected:
	
	float assetScale;
};

#endif /* defined(__Cocos2dXML__CCXMLSprite__) */
