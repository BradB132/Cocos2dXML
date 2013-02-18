//
//  Sequence.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Sequence.h"

void Sequence::createActionObject(cocos2d::CCAction** outAction)
{
	if (!*outAction)
	{
		//assemble a CCArray of new actions
		cocos2d::CCArray* actionArray = cocos2d::CCArray::createWithCapacity(FiniteActions->count());
		cocos2d::ccArray* arr = FiniteActions->data;
		for(int i = 0; i < arr->num; i++)
		{
			cocos2d::CCAction* childAction = NULL;
			((FiniteAction*)arr->arr[i])->createActionObject(&childAction);
			if(childAction)
				actionArray->addObject(childAction);
		}
		
		//CCSpawns launch all the actions at once
		if(serial)
		{
			*outAction = cocos2d::CCSequence::create(actionArray);
		}
		else
		{
			*outAction = cocos2d::CCSpawn::create(actionArray);
		}
	}
	
	Sequence_Base::createActionObject(outAction);
}
