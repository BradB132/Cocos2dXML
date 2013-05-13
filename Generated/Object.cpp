//
//  Object.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/3/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Object.h"

void Object::load()
{
	refreshAllAttributes();
	
	Object_Base::load();
}

void Object::unload()
{
	if(referencedObject)
	{
		referencedObject->release();
		referencedObject = NULL;
	}
	
	Object_Base::unload();
}

bool Object::setValue(std::string newValue)
{
	//swap out the old object for the new one
	setReferencedObject(objectForID(newValue));
	
	return Object_Base::setValue(newValue);
}

void Object::setReferencedObject(cocos2d::CCObject* newObj)
{
	//swap out the old object for the new one
	if(referencedObject)
		referencedObject->release();
	
	referencedObject = newObj;
	
	if(referencedObject)
		referencedObject->retain();
}

NoPL_FunctionValue Object::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue retVal;
	retVal.type = NoPL_DataType_Uninitialized;
	
	//accessors
	if(argc == 0)
	{
		if(!strcmp(functionName, "value"))
		{
			retVal.pointerValue = referencedObject;
			retVal.type = NoPL_DataType_Pointer;
		}
	}
	else
	{
		if(!strcmp(functionName, "setValue"))
		{
			if(argc == 1 && argv[0].type == NoPL_DataType_Pointer)
			{
				setReferencedObject((cocos2d::CCObject*)argv[0].pointerValue);
				
				retVal.booleanValue = true;
				retVal.type = NoPL_DataType_Boolean;
			}
		}
	}
	//return the result if we found one
	if(retVal.type != NoPL_DataType_Uninitialized)
		return retVal;
	return Variable::evaluateFunction(functionName, argv, argc);
}