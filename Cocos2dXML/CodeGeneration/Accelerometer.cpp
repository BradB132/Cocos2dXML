//
//  Accelerometer.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/9/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Accelerometer.h"

void Accelerometer::load()
{
	//zero out all of the values
	accel.x = 0;
	accel.y = 0;
	accel.z = 0;
	gravity.x = 0;
	gravity.y = 0;
	gravity.z = 0;
	
	cocos2d::CCAccelerometer* accelerometer = cocos2d::CCDirector::sharedDirector()->getAccelerometer();
	accelerometer->setDelegate(this);
	accelerometer->setAccelerometerInterval(1.0f/hertz);
	
	Accelerometer_Base::load();
}

void Accelerometer::unload()
{
	cocos2d::CCDirector::sharedDirector()->getAccelerometer()->setDelegate(NULL);
	
	Accelerometer_Base::unload();
}

void Accelerometer::didAccelerate(cocos2d::CCAcceleration* acceleration)
{
	//calculate gravity
	gravity.x = (acceleration->x * filter) + (gravity.x * (1.0 - filter));
	gravity.y = (acceleration->y * filter) + (gravity.y * (1.0 - filter));
	gravity.z = (acceleration->z * filter) + (gravity.x * (1.0 - filter));
	
	//store the raw values from the accelerometer
	accel = *acceleration;
}

NoPL_FunctionValue Accelerometer::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	if(argc == 0)
	{
		if(!strcmp(functionName, "x"))
		{
			returnVal.numberValue = (float)accel.x;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "y"))
		{
			returnVal.numberValue = (float)accel.y;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "z"))
		{
			returnVal.numberValue = (float)accel.z;
			returnVal.type = NoPL_DataType_Number;
		}
		if(!strcmp(functionName, "gravityX"))
		{
			returnVal.numberValue = (float)gravity.x;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "gravityY"))
		{
			returnVal.numberValue = (float)gravity.y;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "gravityZ"))
		{
			returnVal.numberValue = (float)gravity.z;
			returnVal.type = NoPL_DataType_Number;
		}
	}
	
	if(returnVal.type == NoPL_DataType_Uninitialized)
		return Accelerometer_Base::evaluateFunction(functionName, argv, argc);
	return returnVal;
}
