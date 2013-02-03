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

typedef struct
{
	NoPL_Instruction* scriptBuffer;
	unsigned long bufferLength;
	int requireCount;
}RequiredScript;

class Script : public Script_Base
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual void attributeDidChange(int attributeID);
	
	virtual void runTheScript();
	
	static const RequiredScript* requireScriptAtPath(std::string path);
	static void relinquishScriptAtPath(std::string path);
	
protected:
	
	void handleRunEvent(CCObject *obj);
	
	const RequiredScript* script;
};

#endif //end __SCRIPT_H__
