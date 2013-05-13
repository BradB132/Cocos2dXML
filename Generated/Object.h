//
//  Object.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/3/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Object_Base.h"

class Object : public Object_Base
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual bool setValue(std::string newValue);
	
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
	
protected:
	
	void setReferencedObject(cocos2d::CCObject* newObj);
	cocos2d::CCObject* referencedObject;
};

#endif //end __OBJECT_H__
