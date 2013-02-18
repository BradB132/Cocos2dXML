//
//  Scale.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Scale.h"

void Scale::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		if(relative)
			*outAction = cocos2d::CCScaleBy::create(duration, value.x, value.y);
		else
			*outAction = cocos2d::CCScaleTo::create(duration, value.x, value.y);
	}
	
	Scale_Base::createActionObject(outAction);
}
