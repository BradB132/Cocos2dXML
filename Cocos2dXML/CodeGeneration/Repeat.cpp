//
//  Repeat.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Repeat.h"

void Repeat::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		//get the action object that we're easing
		cocos2d::CCAction* innerAction = NULL;
		if(FiniteActions.size() > 0)
			FiniteActions.at(0)->createActionObject(&innerAction);
		
		if(innerAction)
		{
			if(repeats <= 0)
				*outAction = cocos2d::CCRepeatForever::create((cocos2d::CCActionInterval*)innerAction);
			else
				*outAction = cocos2d::CCRepeat::create((cocos2d::CCActionInterval*)innerAction, repeats);
		}
	}
	
	Repeat_Base::createActionObject(outAction);
}