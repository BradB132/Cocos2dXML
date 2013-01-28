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
	
	Action();
	~Action();
	
	virtual void load();
	virtual void unload();
	
	virtual cocos2d::CCAction* getAction();
	
protected:
	
	cocos2d::CCAction* action;
};

#endif //end __ACTION_H__
