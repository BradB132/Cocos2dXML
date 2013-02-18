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
	
	Script();
	
	virtual void load();
	virtual void unload();
	
	virtual void attributeDidChange(int attributeID);
	
	virtual void runTheScript();
	
	virtual cocos2d::CCDictionary* getCurrentParams();
	
	static const RequiredScript* requireScriptAtPath(std::string path);
	static void relinquishScriptAtPath(std::string path);
	
protected:
	
	void handleRunEvent(const char* noteName, cocos2d::CCDictionary* params);
	
	cocos2d::CCDictionary* currentParams;
	const RequiredScript* script;
};

#endif //end __SCRIPT_H__
