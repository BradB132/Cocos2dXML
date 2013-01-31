//
//  Fade.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Fade.h"

void Fade::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		*outAction = cocos2d::CCFadeTo::create(duration, value);
	}
	
	Fade_Base::createActionObject(outAction);
}
