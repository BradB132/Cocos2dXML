//
//  Rotate.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Rotate.h"

void Rotate::createActionObject(cocos2d::CCAction** outAction)
{
	if(!*outAction)
	{
		if(relative)
			*outAction = cocos2d::CCRotateBy::create(duration, value);
		else
			*outAction = cocos2d::CCRotateTo::create(duration, value);
	}
	
	Rotate_Base::createActionObject(outAction);
}
