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
	cocos2d::CCAction* action = createActionObject();
	
	//TODO: get target
	
	//TODO: run on target
}

cocos2d::CCAction* Action::createActionObject()
{
	if(!tempAction)
		tempAction = cocos2d::CCAction::create();
	
	//set all attributes on this action
	cocos2d::CCAction* localAction = tempAction;
	refreshAllAttributes();
	tempAction = NULL;
	
	return localAction;
}

void Action::attributeDidChange(int attributeID)
{
	if(tempAction)
	{
		switch (attributeID)
		{
			case id_Action_tag:
				tempAction->setTag(tag);
				return;
			case id_Action_target:
			case id_Action_startListener:
			case id_Action_stopListener:
				return;
		}
	}
	Action_Base::attributeDidChange(attributeID);
}
