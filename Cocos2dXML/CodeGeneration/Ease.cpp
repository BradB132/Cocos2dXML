//
//  Ease.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Ease.h"

void Ease::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		//get the action object that we're easing
		cocos2d::CCAction* innerAction = NULL;
		if(FiniteActions.size() > 0)
			FiniteActions.at(0)->createActionObject(&innerAction);
		
		if(innerAction)
		{
			switch(type)
			{
				case ease_backIn:
					*outAction = cocos2d::CCEaseBackIn::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_backInOut:
					*outAction = cocos2d::CCEaseBackInOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_backOut:
					*outAction = cocos2d::CCEaseBackOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_bounceIn:
					*outAction = cocos2d::CCEaseBounceIn::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_bounceInOut:
					*outAction = cocos2d::CCEaseBounceInOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_bounceOut:
					*outAction = cocos2d::CCEaseBounceOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_elasticIn:
					*outAction = cocos2d::CCEaseElasticIn::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_elasticInOut:
					*outAction = cocos2d::CCEaseElasticInOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_elasticOut:
					*outAction = cocos2d::CCEaseElasticOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_eponentialIn:
					*outAction = cocos2d::CCEaseExponentialIn::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_eponentialInOut:
					*outAction = cocos2d::CCEaseExponentialInOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_eponentialOut:
					*outAction = cocos2d::CCEaseExponentialOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_in:
					*outAction = cocos2d::CCEaseIn::create((cocos2d::CCActionInterval*)innerAction, rate);
					break;
				case ease_inOut:
					*outAction = cocos2d::CCEaseInOut::create((cocos2d::CCActionInterval*)innerAction, rate);
					break;
				case ease_out:
					*outAction = cocos2d::CCEaseOut::create((cocos2d::CCActionInterval*)innerAction, rate);
					break;
				case ease_sineIn:
					*outAction = cocos2d::CCEaseSineIn::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_sineInOut:
					*outAction = cocos2d::CCEaseSineInOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
				case ease_sineOut:
					*outAction = cocos2d::CCEaseSineOut::create((cocos2d::CCActionInterval*)innerAction);
					break;
			}
		}
	}
	
	Ease_Base::createActionObject(outAction);
}
