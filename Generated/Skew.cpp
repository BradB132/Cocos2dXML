//
//  Skew.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Skew.h"

void Skew::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		if(relative)
			*outAction = cocos2d::CCSkewBy::create(duration, value.x, value.y);
		else
			*outAction = cocos2d::CCSkewTo::create(duration, value.x, value.y);
	}
	
	Skew_Base::createActionObject(outAction);
}
