//
//  Cocos2dXMLTouchDelegate.cpp
//  Cocos2dXML
//
//  Created by Brad Bambara on 2/5/13.
//  Copyright (c) 2013 Robox Studios. All rights reserved.
//

#include "Cocos2dXMLTouchDelegate.h"
#include "Node.h"

void Cocos2dXMLTouchDelegate::initDelegate()
{
	static Cocos2dXMLTouchDelegate* instance = NULL;
	if(!instance)
	{
		instance = new Cocos2dXMLTouchDelegate();
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(instance, 0, false);
	}
}

Cocos2dXMLTouchDelegate::Cocos2dXMLTouchDelegate():
touchToNodeMap(NULL)
{
}

Cocos2dXMLTouchDelegate::~Cocos2dXMLTouchDelegate()
{
	if(touchToNodeMap)
	{
		touchToNodeMap->release();
		touchToNodeMap = NULL;
	}
}

cocos2d::CCNode* Cocos2dXMLTouchDelegate::traverseNodes(cocos2d::CCPoint* touchPos, cocos2d::CCNode* node)
{
	//skip this node if it's not visible
	if(!node->isVisible())
		return NULL;
	
	//get the XML object that is wrapping this node
	Node* wrapper = NULL;
	if(node->getUserData())
		wrapper = (Node*)node->getUserData();
	
	//bail if this node has a wrapper that disables it from touches
	if(wrapper && !wrapper->getEnabled())
		return NULL;
	
	//TODO: check positive vs. negative z orders?
	//recurse through all of the children first because they should be 'in front'
	if(node->getChildren())
	{
		//go backwards through the list to check the 'front' nodes first
		for(int i = node->getChildren()->count()-1; i >= 0; i--)
		{
			cocos2d::CCNode* child = (cocos2d::CCNode*)node->getChildren()->objectAtIndex(i);
			cocos2d::CCNode* foundNode = traverseNodes(touchPos, child);
			if(foundNode)
				return foundNode;
		}
	}
	
	//we've checked every child in front, now check the current node
	if(wrapper && node->hitTest(*touchPos))
		return node;
	
	return NULL;
}

bool Cocos2dXMLTouchDelegate::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//search nodes to set up the touch->node map
	cocos2d::CCPoint point = pTouch->getLocation();
	cocos2d::CCNode* hitNode = traverseNodes(&point, cocos2d::CCDirector::sharedDirector()->getRunningScene());
	
	//did we hit a node?
	if(hitNode && hitNode->getUserData())
	{
		//lazy create this dict
		if(!touchToNodeMap)
		{
			touchToNodeMap = cocos2d::CCDictionary::create();
			touchToNodeMap->retain();
		}
		
		//store this pairing into the map
		touchToNodeMap->setObject(hitNode, pTouch->getID());
		
		//notify the wrapper object of the touch
		((Node*)hitNode->getUserData())->touchDidBegin(pTouch);
	}
	
	return (hitNode != NULL);
}

void Cocos2dXMLTouchDelegate::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(touchToNodeMap)
	{
		cocos2d::CCNode* touchedNode = (cocos2d::CCNode*)touchToNodeMap->objectForKey(pTouch->getID());
		if(touchedNode && touchedNode->getUserData())
			((Node*)touchedNode->getUserData())->touchDidMove(pTouch);
	}
}

void Cocos2dXMLTouchDelegate::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(touchToNodeMap)
	{
		cocos2d::CCNode* touchedNode = (cocos2d::CCNode*)touchToNodeMap->objectForKey(pTouch->getID());
		if(touchedNode && touchedNode->getUserData())
		{
			((Node*)touchedNode->getUserData())->touchDidEnd(pTouch);
			touchToNodeMap->removeObjectForKey(pTouch->getID());
		}
	}
}

void Cocos2dXMLTouchDelegate::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(touchToNodeMap)
	{
		cocos2d::CCNode* touchedNode = (cocos2d::CCNode*)touchToNodeMap->objectForKey(pTouch->getID());
		if(touchedNode && touchedNode->getUserData())
		{
			((Node*)touchedNode->getUserData())->touchDidCancel(pTouch);
			touchToNodeMap->removeObjectForKey(pTouch->getID());
		}
	}
}
