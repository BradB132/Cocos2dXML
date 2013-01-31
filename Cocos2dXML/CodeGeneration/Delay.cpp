//
//  Delay.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Delay.h"

void Delay::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
		*outAction = cocos2d::CCDelayTime::create(duration);
	
	Delay_Base::createActionObject(outAction);
}