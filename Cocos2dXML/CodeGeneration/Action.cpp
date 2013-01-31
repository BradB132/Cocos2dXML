//
//  Action.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Action.h"
#include "actions/CCAction.h"

void Action::runAction()
{
	//create an auto-released action object
	cocos2d::CCAction* action = NULL;
	createActionObject(&action);
	
	//bail if we failed to create it
	if(!action)
		return;
	
	//TODO: get target
	
	//TODO: run on target
}

void Action::createActionObject(cocos2d::CCAction** outAction)
{
	if(*outAction)
		(*outAction)->setTag(tag);
}
