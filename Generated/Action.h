//
//  Action.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __ACTION_H__
#define __ACTION_H__

#import "Action_Base.h"

class CCAction;

class Action : public Action_Base
{
public:
	
	virtual void runAction();
	
	virtual void load();
	virtual void attributeDidChange(int attributeID);
	
	virtual void createActionObject(cocos2d::CCAction** outAction);
	
protected:
	
	void handleStartEvent(const char* noteName, cocos2d::CCDictionary* params);
	void handleStopEvent(const char* noteName, cocos2d::CCDictionary* params);
};

#endif //end __ACTION_H__
