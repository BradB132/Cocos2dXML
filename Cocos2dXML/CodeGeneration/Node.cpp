//
//  Node.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Node.h"

Node::Node():
node(NULL)
{
	
}

Node::~Node()
{
	unload();
}

void Node::load()
{
	//create this node if a subclass hasn't created one already
	if(!node)
	{
		node = cocos2d::CCNode::create();
		node->retain();
	}
	
	//now that we have the node, make sure that all of the properties have been set
	refreshAllAttributes();
	
	//walk up the object graph until we find a parent node
	BaseObject* parentObj = dynamic_cast<BaseObject*>(parent);
	while(parentObj)
	{
		Node* parentNode = dynamic_cast<Node*>(parentObj);
		if(parentNode)
		{
			//we've found the closest parent node, add to this node
			parentNode->getCCNode()->addChild(node);
			break;
		}
		
		parentObj = dynamic_cast<BaseObject*>(parentObj->getParent());
	}
	
	Node_Base::load();
	
	//TODO: auto generate a visitor function for this
	for(int i = 0; i < Nodes->count(); i++)
	{
		Node* child = dynamic_cast<Node*>(Nodes->objectAtIndex(i));
		if(child)
			child->load();
	}
}

void Node::unload()
{
	if(node)
	{
		node->removeFromParentAndCleanup(true);
		node->release();
		node = NULL;
	}
	
	Node_Base::unload();
	
	//TODO: auto generate a visitor function for this
	for(int i = 0; i < Nodes->count(); i++)
	{
		Node* child = dynamic_cast<Node*>(Nodes->objectAtIndex(i));
		if(child)
			child->unload();
	}
}

void Node::refreshAttribute(int attributeID)
{
	if(node)
	{
		switch (attributeID)
		{
			case refresh_Node_zOrder:
				node->setZOrder(zOrder);
				return;
			case refresh_Node_scale:
				node->setScaleX(scale.x);
				node->setScaleY(scale.y);
				return;
			case refresh_Node_position:
				node->setPosition(position);
				return;
			case refresh_Node_skew:
				node->setSkewX(skew.x);
				node->setSkewY(skew.y);
				return;
			case refresh_Node_tag:
				node->setTag(tag);
				return;
			case refresh_Node_anchorPoint:
				node->setAnchorPoint(anchorPoint);
				return;
			case refresh_Node_size:
				node->setContentSize(cocos2d::CCSize(size.x, size.y));
				return;
			case refresh_Node_visible:
				node->setVisible(visible);
				return;
			case refresh_Node_rotation:
				node->setRotation(rotation);
				return;
			case refresh_Node_ignoreAnchorPointForPosition:
				node->ignoreAnchorPointForPosition(ignoreAnchorPointForPosition);
				return;
			case refresh_Node_enabled:
			case refresh_Node_touchThrough:
			case refresh_Node_onTouchUp:
			case refresh_Node_onTouchMove:
			case refresh_Node_onTouchCancel:
				return;
		}
	}
	Node_Base::refreshAttribute(attributeID);
}

cocos2d::CCNode* Node::getCCNode()
{
	return node;
}
