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

#include "APSIntervalGraphicAction.h"
#include "APSActionGroup.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSIntervalGraphicAction_defaultAutoReverse = false;
const float kAPSIntervalGraphicAction_defaultAutoReverseDelay = 0.f;
const unsigned int kAPSIntervalGraphicAction_defaultRepeat = 1;
const int kAPSIntervalGraphicAction_defaultTimingMode = kAPSTimingModeLinear;
const float kAPSIntervalGraphicAction_defaultTimingFactor = 0.f;
const bool kAPSIntervalGraphicAction_defaultFinishRecovery = false;

const string &APSIntervalGraphicAction::getAutoReverseKey() {
    static const string key = "autoReverse";
    return key;
}

const string &APSIntervalGraphicAction::getAutoReverseDelayKey() {
    static const string key = "autoReverseDelay";
    return key;
}

const string &APSIntervalGraphicAction::getRepeatKey() {
    static const string key = "repeat";
    return key;
}

const string &APSIntervalGraphicAction::getTimingModeKey() {
    static const string key = "timingMode";
    return key;
}

const string &APSIntervalGraphicAction::getTimingFactorKey() {
    static const string key = "timingFactor";
    return key;
}

const string &APSIntervalGraphicAction::getFinishRecoveryKey() {
    static const string key = "finishRecovery";
    return key;
}

APSIntervalGraphicAction::APSIntervalGraphicAction(APSDictionary *properties) :
m_autoReverse(kAPSIntervalGraphicAction_defaultAutoReverse),
m_autoReverseDelay(kAPSIntervalGraphicAction_defaultAutoReverseDelay),
m_repeat(kAPSIntervalGraphicAction_defaultRepeat),
m_timingMode(kAPSIntervalGraphicAction_defaultTimingMode),
m_timingFactor(kAPSIntervalGraphicAction_defaultTimingFactor),
m_finishRecovery(kAPSIntervalGraphicAction_defaultFinishRecovery)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSIntervalGraphicAction::~APSIntervalGraphicAction() {
}

bool APSIntervalGraphicAction::initWithProperties(APSDictionary *properties) {
    if(!APSGraphicAction::initWithProperties(properties))
        return false;
    
    APSNumber *number=NULL;
    
    // set autoReverse
    number = (APSNumber *)properties->getObjectForKey(this->getAutoReverseKey());
    if (number) {
        this->setAutoReverse(number->getBoolean());
    }
    
    // set autoReverseDelay
    number = (APSNumber *)properties->getObjectForKey(this->getAutoReverseDelayKey());
    if (number) {
        this->setAutoReverseDelay(number->getFloat());
    }
    
    // set repeat
    number = (APSNumber *)properties->getObjectForKey(this->getRepeatKey());
    if (number) {
        this->setRepeat(number->getUnsignedInteger());
    }
    
    // set timingMode
    number = (APSNumber *)properties->getObjectForKey(this->getTimingModeKey());
    if (number) {
        this->setTimingMode(number->getInteger());
    }
    
    // set timingFactor
    number = (APSNumber *)properties->getObjectForKey(this->getTimingFactorKey());
    if (number) {
        this->setTimingFactor(number->getFloat());
    }
    
    // set finishRecovery
    number = (APSNumber *)properties->getObjectForKey(this->getFinishRecoveryKey());
    if (number) {
        this->setFinishRecovery(number->getBoolean());
    }
    
    return true;
}

float APSIntervalGraphicAction::getEndTime() {
    return this->m_startTime+this->m_duration*this->m_repeat;
}

bool APSIntervalGraphicAction::isRestoringAction() const {
    return !this->m_autoReverse && (this->m_finishRecovery || (this->m_repeat > 1 && !this->m_relative));
}

/*
bool APSIntervalGraphicAction::canCreateUniversalCCAction() const {
    return this->m_autoReverse || this->m_repeat <= 1 || this->m_relative;
}
*/

CCFiniteTimeAction *APSIntervalGraphicAction::universalCCAction(float scale) {
/*    
    if (this->canCreateUniversalCCAction()) {
        APSLOG("universalCCAction() cannot be used.");
        return NULL;
    }
*/
    
    return this->makeMidCCAction(true, scale);
}

void APSIntervalGraphicAction::startFunc() {
    if (this->isRestoringAction()) {
        this->saveNodeState();
    }
    APSAction::startFunc();
    
    /*
    ccTime time = this->getActionGroup()->getElapsedTime()-this->getStartTime();
    if (time > 0.f) {
        [this->m_graphicCCAction performSelector:@selector(setElapsedTime:) withObject:[NSNumber numberWithFloat:time]];
    }
*/
}

void APSIntervalGraphicAction::stopFunc() {
 if (this->isRestoringAction()) {
        this->restoreNodeState();
    }

    APSAction::stopFunc();
    
}

CCFiniteTimeAction *APSIntervalGraphicAction::makeMidCCAction(bool universal, float scale) {
    m_graphicCCAction = this->makeGraphicCCAction(universal, scale);
    CCActionInterval *action = this->attachTimingMode(m_graphicCCAction);
    
    if (this->m_autoReverse) {
        
        if (this->getAutoReverseDelay() > FLT_EPSILON) {
#if COCOS2D_VERSION >= 0x00020000
            action = CCSequence::create(action, CCDelayTime::create(this->getAutoReverseDelay()));
#else
            action = CCSequence::actionOneTwo(action, CCDelayTime::actionWithDuration(this->getAutoReverseDelay()));
#endif//APS_SKIP
        }
        
#if COCOS2D_VERSION >= 0x00020000
        action = CCSequence::create(action, action->reverse());
#else
        action = CCSequence::actionOneTwo(action, action->reverse());
#endif//APS_SKIP
    }

    return this->attachRepeat(action);
}

CCActionInterval *APSIntervalGraphicAction::attachRepeat(CCActionInterval *action) {
    if (this->m_repeat > 1) {
        CCActionInterval *actionWithRestoring = NULL;
        
        if (this->isRestoringAction()) {
            // For repeating non-relative and non-autoreverse action, we should bring graphic's state to origin.
#if COCOS2D_VERSION >= 0x00020000
            actionWithRestoring = CCSequence::create(action,
                                                           CCCallFunc::create(this, callfunc_selector(APSGraphicAction::restoreNodeState)));
#else
            actionWithRestoring = CCSequence::actionOneTwo(action,
                                                           CCCallFunc::actionWithTarget(this, callfunc_selector(APSGraphicAction::restoreNodeState)));
#endif//APS_SKIP
        }
        
        if(this->m_repeat > 1) {
#if COCOS2D_VERSION >= 0x00020000
            if (actionWithRestoring) {
                // The last action should not restore state, so we append the original action.
                action = CCSequence::create(CCRepeat::create(actionWithRestoring, this->m_repeat-1), action);
            } else {
                action = CCRepeat::create(action, this->m_repeat);
            }
#else
            if (actionWithRestoring) {
                // The last action should not restore state, so we append the original action.
                action = CCSequence::actionOneTwo(CCRepeat::actionWithAction(actionWithRestoring, this->m_repeat-1), action);
            } else {
                action = CCRepeat::actionWithAction(action, this->m_repeat);
            }
#endif//APS_SKIP
        }
    }
    return action;
}

CCActionInterval *APSIntervalGraphicAction::attachTimingMode(CCActionInterval *action) {
    switch (this->m_timingMode) {
        case kAPSTimingModeEaseIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseIn::create(action, this->m_timingFactor);
#else
            action = CCEaseIn::actionWithAction(action, this->m_timingFactor);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseOut::create(action, this->m_timingFactor);
#else
            action = CCEaseOut::actionWithAction(action, this->m_timingFactor);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseInEaseOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseInOut::create(action ,this->m_timingFactor);
#else
            action = CCEaseInOut::actionWithAction(action ,this->m_timingFactor);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseExponentialIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseExponentialIn::create(action);
#else
            action = CCEaseExponentialIn::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseExponentialOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseExponentialOut::create(action);
#else
            action = CCEaseExponentialOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseExponentialInOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseExponentialInOut::create(action);
#else
            action = CCEaseExponentialInOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseSineIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseSineIn::create(action);
#else
            action = CCEaseSineIn::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseSineOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseSineOut::create(action);
#else
            action = CCEaseSineOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseSineInOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseSineInOut::create(action);
#else
            action = CCEaseSineInOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseElasticIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseElasticIn::create(action ,easeElasticPeriod(this->m_timingFactor));
#else
            action = CCEaseElasticIn::actionWithAction(action ,easeElasticPeriod(this->m_timingFactor));
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseElasticOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseElasticOut::create(action ,easeElasticPeriod(this->m_timingFactor));
#else
            action = CCEaseElasticOut::actionWithAction(action ,easeElasticPeriod(this->m_timingFactor));
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseElasticInOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseElasticInOut::create(action ,easeElasticPeriod(this->m_timingFactor));
#else
            action = CCEaseElasticInOut::actionWithAction(action ,easeElasticPeriod(this->m_timingFactor));
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBounceIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBounceIn::create(action);
#else
            action = CCEaseBounceIn::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBounceOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBounceOut::create(action);
#else
            action = CCEaseBounceOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBounceInOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBounceInOut::create(action);
#else
            action = CCEaseBounceInOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBackIn:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBackIn::create(action);
#else
            action = CCEaseBackIn::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBackOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBackOut::create(action);
#else
            action = CCEaseBackOut::actionWithAction(action);
#endif//APS_SKIP
            break;
        case kAPSTimingModeEaseBackInOut:
#if COCOS2D_VERSION >= 0x00020000
            action = CCEaseBackInOut::create(action);
#else
            action = CCEaseBackInOut::actionWithAction(action);
#endif//APS_SKIP
            break;
            
        default:
            break;
    }
    return action;
    
}

APS_END_NAMESPACE

