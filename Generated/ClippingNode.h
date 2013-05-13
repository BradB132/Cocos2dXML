//
//  ClippingNode.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __CLIPPINGNODE_H__
#define __CLIPPINGNODE_H__

#import "ClippingNode_Base.h"

class ClippingNode : public ClippingNode_Base
{
	virtual void load();
	
	//overridden mutators
	virtual bool setAlphaThreshold(float newAlphaThreshold);
	virtual bool setInverted(bool newInverted);
};

#endif //end __CLIPPINGNODE_H__
