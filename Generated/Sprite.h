//
//  Sprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#import "Sprite_Base.h"

class Sprite : public Sprite_Base
{
public:
	virtual void load();
	
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
	
	//overridden mutators
	virtual bool setColor(Cocos2dXMLColor newColor);
	virtual bool setTexture(Cocos2dXMLFilePath newTexture);
	virtual bool setFlipX(bool newFlipX);
	virtual bool setFlipY(bool newFlipY);
	virtual bool setSrcBlend(srcBlendFunc newSrcBlend);
	virtual bool setDstBlend(dstBlendFunc newDstBlend);
};

#endif //end __SPRITE_H__
