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
	
	virtual void refreshAttribute(int attributeID);
};

#endif //end __SPRITE_H__
