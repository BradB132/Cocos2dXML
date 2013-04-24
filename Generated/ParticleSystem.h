//
//  ParticleSystem.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#import "ParticleSystem_Base.h"

class ParticleSystem : public ParticleSystem_Base
{
public:
	
	virtual void load();
	
	virtual bool setEmitting(bool newEmitting);
	
	//TODO: fix and remove this
	virtual void refreshAllAttributes();
	
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
};

#endif //end __PARTICLESYSTEM_H__
