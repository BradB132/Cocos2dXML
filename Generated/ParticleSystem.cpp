//
//  ParticleSystem.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "ParticleSystem.h"

void ParticleSystem::load()
{
	if(!node)
	{
		node = cocos2d::CCParticleSystemQuad::create(plist.c_str());
		node->retain();
	}
	
	ParticleSystem_Base::load();
}

void ParticleSystem::refreshAllAttributes()
{
	//TODO: fix and remove this
	setEmitting(emitting);
	
	ParticleSystem_Base::refreshAllAttributes();
}

bool ParticleSystem::setEmitting(bool newEmitting)
{
	if(node)
	{
		if(newEmitting)
			((cocos2d::CCParticleSystemQuad*)node)->startSystem();
		else
			((cocos2d::CCParticleSystemQuad*)node)->stopSystem();
	}
	
	return ParticleSystem_Base::setEmitting(newEmitting);
}

NoPL_FunctionValue ParticleSystem::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue retVal;
	retVal.type = NoPL_DataType_Uninitialized;
	
	if(argc == 0)
	{
		if(!strcmp(functionName, "resetSystem") || !strcmp(functionName, "reset"))
		{
			((cocos2d::CCParticleSystem*)node)->resetSystem();
		}
	}
	
	//return the result if we found one
	if(retVal.type != NoPL_DataType_Uninitialized)
		return retVal;
	return ParticleSystem_Base::evaluateFunction(functionName, argv, argc);
}