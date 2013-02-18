//
//  Accelerometer.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/9/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "Accelerometer_Base.h"
#include "platform/CCAccelerometerDelegate.h"

class Accelerometer : public Accelerometer_Base, public cocos2d::CCAccelerometerDelegate
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
	
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
	
protected:
	
	cocos2d::CCAcceleration accel;
	cocos2d::CCAcceleration gravity;
	
};

#endif //end __ACCELEROMETER_H__
