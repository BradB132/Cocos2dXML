//
//  Delay.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Delay.h"

cocos2d::CCAction* Delay::createActionObject()
{
	if(!tempAction)
		tempAction = cocos2d::CCDelayTime::create(duration);
	
	return Delay_Base::createActionObject();
}