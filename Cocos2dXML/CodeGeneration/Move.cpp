//
//  Move.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Move.h"

void Move::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		if(relative)
			*outAction = cocos2d::CCMoveBy::create(duration, value);
		else
			*outAction = cocos2d::CCMoveTo::create(duration, value);
	}
	
	Move_Base::createActionObject(outAction);
}
