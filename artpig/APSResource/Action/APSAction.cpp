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

#include <iostream>
#include "APSAction.h"
#include "APSActionGroup.h"
#include "APSGraphicGroup.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSAction_defaultEnabled = true;
const int kAPSAction_defaultPriority = 0;


const string &APSAction::getTargetGraphicIndexKey() {
    static const string key = "targetGraphicIndex";
    return key;
}

const string &APSAction::getActionGroupIndexKey() {
    static const string key = "actionGroupIndex";
    return key;
}

const string &APSAction::getPriorityKey() {
    static const string key = "priority";
    return key;
}

const string &APSAction::getEnabledKey() {
    static const string key = "enabled";
    return key;
}

const string &APSAction::getStartTimeKey() {
    static const string key = "startTime";
    return key;
}

const string &APSAction::getDurationKey() {
    static const string key = "duration";
    return key;
}

const string &APSAction::getRunningKey() {
    static const string key = "running";
    return key;
}

APSAction::APSAction(APSDictionary *properties) :
m_targetGraphic(NULL),
m_targetGraphicIndex(APS_NIL_INDEX),
m_actionGroup(NULL),
m_actionGroupIndex(APS_NIL_INDEX),
m_ccAction(NULL),
m_priority(kAPSAction_defaultPriority),
m_startTime(0.f),
m_duration(0.f),
m_enabled(kAPSAction_defaultEnabled),
m_running(false)//,
//m_midCCAction(NULL)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSAction::~APSAction() {
    CC_SAFE_RELEASE_NULL(this->m_ccAction);
}

bool APSAction::initWithProperties(APSDictionary *properties) {
    
    if(!APSResource::initWithProperties(properties))
        return false;
    
    // set targetGraphicIndex
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getTargetGraphicIndexKey());
    if (number) {
        this->setTargetGraphicIndex(APSNumber::indexWithNumber(number));
    }
    
    // set actionGroupIndex
    number = (APSNumber *)properties->getObjectForKey(this->getActionGroupIndexKey());
    if (number) {
        this->setActionGroupIndex(APSNumber::indexWithNumber(number));
    }
    
    // set priority
    number = (APSNumber *)properties->getObjectForKey(this->getPriorityKey());
    if (number) {
        this->setPriority(number->getInteger());
    }
    
    // set enabled
    number = (APSNumber *)properties->getObjectForKey(this->getEnabledKey());
    if (number) {
        this->setEnabled(number->getBoolean());
    }
    
    // set startTime
    number = (APSNumber *)properties->getObjectForKey(this->getStartTimeKey());
    if (number) {
        this->setStartTime(number->getFloat());
    }
    
    // set duration
    number = (APSNumber *)properties->getObjectForKey(this->getDurationKey());
    if (number) {
        this->setDuration(number->getFloat());
    }
    
    return true;
}


float APSAction::getEndTime() {
    return this->m_startTime+this->m_duration;
}

CCAction *APSAction::getCCAction() {
    if (!this->m_ccAction) {
        // create if does not have one.
        this->m_ccAction = this->makeCCAction();
        CC_SAFE_RETAIN(this->m_ccAction);
    }
    return this->m_ccAction;
}

void APSAction::resetCCAction() {
    // Force to stop currently running action.
    if (this->getRunning()) {
        this->interrupt();
    }
    
    CC_SAFE_RELEASE_NULL(this->m_ccAction);
    
    this->getCCAction();
}

void APSAction::clearCachedData() { 
    if (this->m_ccAction) {
        if(this->m_ccAction->isDone()) {
            CC_SAFE_RELEASE_NULL(this->m_ccAction);
            this->m_ccAction = NULL;
        }
    }
}

void APSAction::preloadData() {
    if (!this->m_ccAction) {
        this->getCCAction();
    }
}

void APSAction::startFunc() {
    this->m_running = true;
    this->getParentSymbol()->notifyStart(this);
}

void APSAction::stopFunc() {
    APSGraphicGroup *graphic = this->getTargetGraphic();
    if (graphic) {
        graphic->stopAction(this);
    }
    this->m_running = false;
    this->getParentSymbol()->notifyStop(this);
}

void APSAction::trigger() {
    this->getParentSymbol()->triggerAction(this);
}

void APSAction::interrupt() {
    this->getParentSymbol()->interruptAction(this);
}

void APSAction::_trigger() {

    this->getTargetGraphic()->runAction(this);
}

void APSAction::_interrupt() {
    // Since CCAction is stopped, stopFunc() should be called manually.
    this->stopFunc();
}

CCFiniteTimeAction * APSAction::makeCCAction() {
    float scale = APSPlatform::sharedPlatform()->getScaleFactor();
    
    CCFiniteTimeAction *actions[3] = { this->makePreCCAction(), this->makeMidCCAction(false, 1/scale), this->makePostCCAction() };
    
    CCFiniteTimeAction *seq = NULL;
    for (int i=0; i < 3; i++) {
        if (actions[i]) {
            if (seq) {
#if COCOS2D_VERSION >= 0x00020000
                seq = CCSequence::create(seq, actions[i]);
#else
                seq = CCSequence::actionOneTwo(seq, actions[i]);
#endif//APS_SKIP
                            } else {
                seq = actions[i];
            }
        }
    }
#if COCOS2D_VERSION >= 0x00020000
    CCFiniteTimeAction *action = seq ? seq : CCMoveBy::create(FLT_EPSILON, CCPointZero);
#else
    CCFiniteTimeAction *action = seq ? seq : CCMoveBy::actionWithDuration(FLT_EPSILON, CCPointZero);
#endif//APS_SKIP
        
    return action;
//    this->m_midCCAction = actions[1];
}

CCFiniteTimeAction * APSAction::makePreCCAction() {
    // execute startFunc
#if COCOS2D_VERSION >= 0x00020000
    return CCCallFunc::create(this, callfunc_selector(APSAction::startFunc));
#else
    return CCCallFunc::actionWithTarget(this, callfunc_selector(APSAction::startFunc));
#endif//APS_SKIP
    }

CCFiniteTimeAction * APSAction::makePostCCAction() {
    // execute stopFunc
#if COCOS2D_VERSION >= 0x00020000
    return CCCallFunc::create(this, callfunc_selector(APSAction::stopFunc));
#else
    return CCCallFunc::actionWithTarget(this, callfunc_selector(APSAction::stopFunc));
#endif//APS_SKIP
    }

APSGraphicGroup *APSAction::getTargetGraphic() {
    if (this->getTargetGraphicIndex()==APS_NIL_INDEX) {
        return NULL;
    }
    
    if (!m_targetGraphic) {
        m_targetGraphic = (APSGraphicGroup *)this->getResource(this->getTargetGraphicIndex());
    }
    
    return m_targetGraphic;
}

APSActionGroup *APSAction::getActionGroup() {
    if (this->getActionGroupIndex() == APS_NIL_INDEX) {
        return NULL;
    }
    
    if (!m_actionGroup) {
        m_actionGroup = (APSActionGroup *)this->getResource(this->getActionGroupIndex());
    }
    
    return m_actionGroup;
}

APS_END_NAMESPACE


