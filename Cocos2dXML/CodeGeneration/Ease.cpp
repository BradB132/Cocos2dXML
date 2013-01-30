//
//  Ease.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Ease.h"

cocos2d::CCAction* Ease::createActionObject()
{
	if(!tempAction)
	{
		//get the action object that we're easing
		cocos2d::CCActionInterval* innerAction = NULL;
		if(FiniteActions.size() > 0)
			innerAction = (cocos2d::CCActionInterval*)FiniteActions.at(0)->createActionObject();
		
		if(innerAction)
		{
			switch(type)
			{
				case ease_backIn:
					tempAction = cocos2d::CCEaseBackIn::create(innerAction);
					break;
				case ease_backInOut:
					tempAction = cocos2d::CCEaseBackInOut::create(innerAction);
					break;
				case ease_backOut:
					tempAction = cocos2d::CCEaseBackOut::create(innerAction);
					break;
				case ease_bounceIn:
					tempAction = cocos2d::CCEaseBounceIn::create(innerAction);
					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
//				case ease_:
//					tempAction = cocos2d::CCEase ::create(innerAction);
//					break;
					
			}
		}
	}
	
	return Ease_Base::createActionObject();
}

void Ease::attributeDidChange(int attributeID)
{
	//TODO:
}
