/****************************************************************************
 Copyright (c) 2012 ArtPig Software LLC
 
 http://www.artpigsoft.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "APSInstantMoveAction.h"
#include "APSGraphicGroup.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const string &APSInstantMoveAction::getEndPositionKey() {
    static const string key = "endPosition";
    return key;
}

APSInstantMoveAction::APSInstantMoveAction(APSDictionary *properties) :
m_endPosition(CCPointZero)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSInstantMoveAction::~APSInstantMoveAction() {
}

bool APSInstantMoveAction::initWithProperties(APSDictionary *properties) {
    if(!APSInstantGraphicAction::initWithProperties(properties))
        return false;
    
    APSString *str = (APSString *)properties->getObjectForKey(this->getEndPositionKey());
    if (str) {
        this->setEndPosition(str->getPointValue());
    }
    
    /*
     Version 1.0.1
    // set endPosition
    APSNumber *number = (APSNumber *)properties->getObjectForKey(kAPSInstantMoveAction_endPositionXKey);
    if (number) {
        this->m_endPosition.x = number->getFloat();
    }
    
    number = (APSNumber *)properties->getObjectForKey(kAPSInstantMoveAction_endPositionYKey);
    if (number) {
        this->m_endPosition.y = number->getFloat();
    }
    */
    return true;
    
}

#pragma #### Protected ####

void APSInstantMoveAction::instantMove(CCNode* pSender) {
    if (this->getRelative()) {
        CCPoint ss = this->getTargetGraphic()->getNode()->getPosition();
        CCPoint es = this->getEndPosition();
        pSender->setPosition(ccp(ss.x+es.x, ss.y+es.y));
    } else {
        pSender->setPosition(this->getEndPosition());
    }
}

// Makes a CCFiniteTimeAction that runs between pre and post actions.
CCFiniteTimeAction * APSInstantMoveAction::makeMidCCAction(bool universal, float scale) {
#if COCOS2D_VERSION >= 0x00020000
    return CCCallFuncN::create(this, callfuncN_selector(APSInstantMoveAction::instantMove));
#else
    return CCCallFuncN::actionWithTarget(this, callfuncN_selector(APSInstantMoveAction::instantMove));
#endif//APS_SKIP
}

APS_END_NAMESPACE
