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

void ClippingNode::attributeDidChange(int attributeID)
{
	if(node)
	{
		cocos2d::CCClippingNode* clip = (cocos2d::CCClippingNode*)node;
		switch (attributeID)
		{
			case id_ClippingNode_alphaThreshold:
				clip->setAlphaThreshold(alphaThreshold);
				return;
			case id_ClippingNode_inverted:
				clip->setInverted(inverted);
				return;
		}
	}
	ClippingNode_Base::attributeDidChange(attributeID);
}