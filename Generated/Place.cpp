//
//  Place.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Place.h"

void Place::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		*outAction = cocos2d::CCPlace::create(value);
	}
	
	Place_Base::createActionObject(outAction);
}