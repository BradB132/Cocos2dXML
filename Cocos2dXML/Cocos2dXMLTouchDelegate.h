//
//  Cocos2dXMLTouchDelegate.h
//  Cocos2dXML
//
//  Created by Brad Bambara on 2/5/13.
//  Copyright (c) 2013 Robox Studios. All rights reserved.
//

#ifndef __Cocos2dXML__Cocos2dXMLTouchDelegate__
#define __Cocos2dXML__Cocos2dXMLTouchDelegate__

#include <iostream>
#include "cocos2d.h"

class Cocos2dXMLTouchDelegate : public cocos2d::CCObject, public cocos2d::CCTouchDelegate
{
public:
	
	Cocos2dXMLTouchDelegate();
	~Cocos2dXMLTouchDelegate();
	
	static void initDelegate();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
protected:
	
	virtual cocos2d::CCNode* traverseNodes(cocos2d::CCPoint* touchPos, cocos2d::CCNode* node);
	cocos2d::CCDictionary* touchToNodeMap;
};

#endif /* defined(__Cocos2dXML__Cocos2dXMLTouchDelegate__) */
