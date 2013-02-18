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

#include "APSInstantScaleAction.h"
#include "APSGraphicGroup.h"
//#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const string &APSInstantScaleAction::getEndScaleKey() {
    static const string key = "endScale";
    return key;
}

APSInstantScaleAction::APSInstantScaleAction(APSDictionary *properties) :
m_endScale(CCPointZero)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSInstantScaleAction::~APSInstantScaleAction() {
}

bool APSInstantScaleAction::initWithProperties(APSDictionary *properties) {
    if(!APSInstantGraphicAction::initWithProperties(properties))
        return false;
    
    // set endScale
    APSString *str = (APSString *)properties->getObjectForKey(this->getEndScaleKey());
    if (str) {
        this->m_endScale = str->getPointValue();
    }
    
    /*
     version 1.0.1
    APSNumber *number = (APSNumber *)properties->getObjectForKey(kAPSInstantScaleAction_endScaleXKey);
    if (number) {
        this->m_endScale.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSInstantScaleAction_endScaleYKey);
    if (number) {
        this->m_endScale.y = number->getFloat();
    }
    */
    return true;
    
}

#pragma #### Protected ####

void APSInstantScaleAction::instantScale(CCNode* pSender) {
    CCNode *node = this->getTargetGraphic()->getNode();
    CCPoint ss = CCPoint(node->getScaleX(), node->getScaleY());
    CCPoint es = this->getEndScale();
    if (this->getRelative()) {
        pSender->setScaleX(ss.x+es.x);
        pSender->setScaleY(ss.y+es.y);
    } else {
        pSender->setScaleX(es.x);
        pSender->setScaleY(es.y);
    }
}

CCFiniteTimeAction * APSInstantScaleAction::makeMidCCAction(bool universal, float scale) {
#if COCOS2D_VERSION >= 0x00020000
    return CCCallFuncN::create(this, callfuncN_selector(APSInstantScaleAction::instantScale));
#else
    return CCCallFuncN::actionWithTarget(this, callfuncN_selector(APSInstantScaleAction::instantScale));
#endif//APS_SKIP
}

APS_END_NAMESPACE

