//
//  ClippingNode.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "ClippingNode.h"

void ClippingNode::load()
{
	if(!node)
	{
		node = cocos2d::CCClippingNode::create();
		node->retain();
	}
	
	ClippingNode_Base::load();
}

bool ClippingNode::setAlphaThreshold(float newAlphaThreshold)
{
	if(node)
		((cocos2d::CCClippingNode*)node)->setAlphaThreshold(newAlphaThreshold);
	return ClippingNode_Base::setAlphaThreshold(newAlphaThreshold);
}

bool ClippingNode::setInverted(bool newInverted)
{
	if(node)
		((cocos2d::CCClippingNode*)node)->setInverted(newInverted);
	return ClippingNode_Base::setInverted(newInverted);
}
