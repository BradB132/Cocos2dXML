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

#include "APSScaleAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSScaleAction::getEndScaleKey() {
    static const string key = "endScale";
    return key;
}

APSScaleAction::APSScaleAction(APSDictionary *properties) :
m_startScale(CCPointZero),
m_endScale(CCPointZero)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSScaleAction::~APSScaleAction() {
}

bool APSScaleAction::initWithProperties(APSDictionary *properties) {
    bool ok = APSIntervalGraphicAction::initWithProperties(properties);
    
    // set endScale
    APSString *str = (APSString *)properties->getObjectForKey(this->getEndScaleKey());
    if (str) {
        this->m_endScale = str->getPointValue();
    }

    /*
     v1.0.1
    APSNumber *number = (APSNumber *)properties->getObjectForKey(kAPSScaleAction_endScaleXKey);
    if (number) {
        this->m_endScale.x = number->getFloat();
    }
    
    number = (APSNumber *)properties->getObjectForKey(kAPSScaleAction_endScaleYKey);
    if (number) {
        this->m_endScale.y = number->getFloat();
    }
    */
    return ok;
    
}

#pragma #### Protected ####

void APSScaleAction::saveNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        CCNode *node = graphic->getNode();
        this->m_startScale.x = node->getScaleX();
        this->m_startScale.y = node->getScaleY();
    }
}

void APSScaleAction::restoreNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        CCNode *node = graphic->getNode();
        node->setScaleX(this->m_startScale.x);
        node->setScaleY(this->m_startScale.y);
    }
}

CCActionInterval *APSScaleAction::makeGraphicCCAction(bool universal, float scale) {
    // If universal==false, APSScaleAction manages restoring graphic states, then there is no need CCAction to restore graphic state.
    bool finishRecovery = universal && this->isRestoringAction();
    if (this->getRelative()) {
        return APSCCScaleBy::actionWithDuration(this->getDuration(), this->m_endScale.x, this->m_endScale.y, finishRecovery);
    } else {
        return APSCCScaleTo::actionWithDuration(this->getDuration(), this->m_endScale.x, this->m_endScale.y, finishRecovery);
    }
}

APS_END_NAMESPACE
