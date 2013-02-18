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

#include "APSRotationAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const string &APSRotationAction::getEndRotationKey() {
    static const string key = "endRotation";
    return key;
}

APSRotationAction::APSRotationAction(APSDictionary *properties) :
m_startRotation(0.f),
m_endRotation(0.f)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSRotationAction::~APSRotationAction() {
}


bool APSRotationAction::initWithProperties(APSDictionary *properties) {
    bool ok = APSIntervalGraphicAction::initWithProperties(properties);
    
    // set endRotation
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getEndRotationKey());
    if (number) {
        this->m_endRotation = number->getFloat();
    }
    
    return ok;
}

#pragma #### Protected ####

// 액션 시작시 현재의 위치를 저장
void APSRotationAction::saveNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        this->m_startRotation = graphic->getNode()->getRotation();
    }
}

void APSRotationAction::restoreNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        graphic->getNode()->setRotation(this->m_startRotation);
    }
}

CCActionInterval *APSRotationAction::makeGraphicCCAction(bool universal, float scale) {
    // If universal==false, APSRotationAction manages restoring graphic states, then there is no need CCAction to restore graphic state.
    bool finishRecovery = universal && this->isRestoringAction();
    if (this->getRelative()) {
        return APSCCRotateBy::actionWithDuration(this->getDuration(), this->getEndRotation(), finishRecovery);
    } else {
        return APSCCRotateTo::actionWithDuration(this->getDuration(), this->getEndRotation(), finishRecovery);
    }
}

APS_END_NAMESPACE
