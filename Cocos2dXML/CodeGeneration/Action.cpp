//
//  Action.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Action.h"
#include "actions/CCAction.h"

Action::Action():
action(NULL)
{
}

Action::~Action()
{
	unload();
}

void Action::load()
{
	if(!action)
	{
		action = cocos2d::CCAction::create();
	}
	
	refreshAllAttributes();
	
	Action_Base::load();
}

void Action::unload()
{
	if(action)
	{
		action->release();
		action = NULL;
	}
	
	Action_Base::unload();
}

cocos2d::CCAction* Action::getAction()
{
	return action;
}
