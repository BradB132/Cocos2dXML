//
//  Tint.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Tint.h"

void Tint::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		*outAction = cocos2d::CCTintTo::create(duration, value.r, value.g, value.b);
	}
	
	Tint_Base::createActionObject(outAction);
}