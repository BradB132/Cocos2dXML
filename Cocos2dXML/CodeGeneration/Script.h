//
//  Script.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/1/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "Script_Base.h"

class Script : public Script_Base
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual void runScript();
};

#endif //end __SCRIPT_H__
