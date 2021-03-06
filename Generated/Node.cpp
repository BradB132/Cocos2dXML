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
	
	//set up a reference to this object on the node
	node->setUserData(this);
	
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
}

bool Node::setZOrder(int newZOrder)
{
	if(node)
		node->setZOrder(newZOrder);
	return Node_Base::setZOrder(newZOrder);
}

bool Node::setScale(cocos2d::CCPoint newScale)
{
	if(node)
	{
		node->setScaleX(newScale.x);
		node->setScaleY(newScale.y);
	}
	return Node_Base::setScale(newScale);
}

bool Node::setPosition(cocos2d::CCPoint newPosition)
{
	if(node)
		node->setPosition(newPosition);
	return Node_Base::setPosition(newPosition);
}

bool Node::setSkew(cocos2d::CCPoint newSkew)
{
	if(node)
	{
		node->setSkewX(newSkew.x);
		node->setSkewY(newSkew.y);
	}
	return Node_Base::setSkew(newSkew);
}

bool Node::setTag(int newTag)
{
	if(node)
		node->setTag(newTag);
	return Node_Base::setTag(newTag);
}

bool Node::setAnchorPoint(cocos2d::CCPoint newAnchorPoint)
{
	if(node)
		node->setAnchorPoint(newAnchorPoint);
	return Node_Base::setAnchorPoint(newAnchorPoint);
}

bool Node::setSize(cocos2d::CCPoint newSize)
{
	if(node)
		node->setContentSize(cocos2d::CCSize(newSize.x, newSize.y));
	return Node_Base::setSize(newSize);
}

bool Node::setVisible(bool newVisible)
{
	if(node)
		node->setVisible(newVisible);
	return Node_Base::setVisible(newVisible);
}

bool Node::setRotation(float newRotation)
{
	if(node)
		node->setRotation(newRotation);
	return Node_Base::setRotation(newRotation);
}

bool Node::setIgnoreAnchorPointForPosition(bool newIgnoreAnchorPointForPosition)
{
	if(node)
		node->ignoreAnchorPointForPosition(newIgnoreAnchorPointForPosition);
	return Node_Base::setIgnoreAnchorPointForPosition(newIgnoreAnchorPointForPosition);
}

cocos2d::CCNode* Node::getCCNode()
{
	return node;
}

#pragma mark - Touch notification

void Node::touchDidBegin(cocos2d::CCTouch* touch)
{
	if(onTouchDown != "")
	{
		cocos2d::CCDictionary* params = NULL;
		if(touch)
		{
			params = cocos2d::CCDictionary::create();
			params->setObject(touch, "touch");
		}
		postEvent(onTouchDown, params);
	}
}

void Node::touchDidMove(cocos2d::CCTouch* touch)
{
	if(onTouchMove != "")
	{
		cocos2d::CCDictionary* params = NULL;
		if(touch)
		{
			params = cocos2d::CCDictionary::create();
			params->setObject(touch, "touch");
		}
		postEvent(onTouchMove, params);
	}
}

void Node::touchDidEnd(cocos2d::CCTouch* touch)
{
	if(onTouchUp != "")
	{
		cocos2d::CCDictionary* params = NULL;
		if(touch)
		{
			params = cocos2d::CCDictionary::create();
			params->setObject(touch, "touch");
		}
		postEvent(onTouchUp, params);
	}
}

void Node::touchDidCancel(cocos2d::CCTouch* touch)
{
	if(onTouchCancel != "")
	{
		cocos2d::CCDictionary* params = NULL;
		if(touch)
		{
			params = cocos2d::CCDictionary::create();
			params->setObject(touch, "touch");
		}
		postEvent(onTouchCancel, params);
	}
}

NoPL_FunctionValue Node::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	if(node)
	{
		if(argc == 0)
		{
			if(!strcmp(functionName, "worldPositionX"))
			{
				returnVal.numberValue = node->convertToWorldSpaceAR(cocos2d::CCPointZero).x;
				returnVal.type = NoPL_DataType_Number;
			}
			else if(!strcmp(functionName, "worldPositionY"))
			{
				returnVal.numberValue = node->convertToWorldSpaceAR(cocos2d::CCPointZero).y;
				returnVal.type = NoPL_DataType_Number;
			}
		}
		else if(!strcmp(functionName, "hitTest"))
		{
			if(argc == 2 &&
			   argv[0].type == NoPL_DataType_Number &&
			   argv[1].type == NoPL_DataType_Number)
			{
				returnVal.booleanValue = (node->hitTest(cocos2d::CCPoint(argv[0].numberValue, argv[1].numberValue)));
				returnVal.type = NoPL_DataType_Boolean;
			}
			else if(argc == 1 && argv[0].type == NoPL_DataType_Pointer)
			{
				cocos2d::CCObject* arg = (cocos2d::CCObject*)argv[0].pointerValue;
				Node* otherNode = dynamic_cast<Node*>(arg);
				if(otherNode && otherNode->getCCNode())
				{
					//get the transforms for each node
					cocos2d::CCAffineTransform thisTransform = node->nodeToWorldTransform();
					cocos2d::CCAffineTransform nodeTransform = otherNode->getCCNode()->nodeToWorldTransform();
					
					//create a rect for each node in the same coord system
					cocos2d::CCRect thisRect;
					thisRect.origin = CCPointApplyAffineTransform(cocos2d::CCPoint(0,0), thisTransform);
					thisRect.size = CCSizeApplyAffineTransform(node->getContentSize(), thisTransform);
					cocos2d::CCRect nodeRect;
					nodeRect.origin = CCPointApplyAffineTransform(cocos2d::CCPoint(0,0), nodeTransform);
					nodeRect.size = CCSizeApplyAffineTransform(otherNode->getCCNode()->getContentSize(), nodeTransform);
					
					//return the result of the hit test
					returnVal.booleanValue = thisRect.intersectsRect(nodeRect);
					returnVal.type = NoPL_DataType_Boolean;
				}
			}
		}
	}
	
	if(returnVal.type == NoPL_DataType_Uninitialized)
		return Node_Base::evaluateFunction(functionName, argv, argc);
	return returnVal;
}
