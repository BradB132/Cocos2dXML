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

#include "APSLinkerAction.h"
#include "APSActionGroup.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


//const float kAPSLinkerAction_defaultDelay = 0.f;
const APSLinkerType kAPSLinkerAction_defaultType = kAPSLinkerTypeTrigger;
const bool kAPSLinkerAction_defaultNoTriggerRunningTarget = false;


const string &APSLinkerAction::getTargetActionIndexKey() {
    static const string key = "tActionIdx";
    return key;
}

const string &APSLinkerAction::getTypeKey() {
    static const string key = "type";
    return key;
}

const string &APSLinkerAction::getNoTriggerRunningTargetKey() {
    static const string key = "noTrigRT";
    return key;
}

APSLinkerAction::APSLinkerAction(APSDictionary *properties) :
m_type(kAPSLinkerAction_defaultType),
m_targetAction(NULL),
m_targetActionIndex(APS_NIL_INDEX),
m_noTriggerRunningTarget(kAPSLinkerAction_defaultNoTriggerRunningTarget)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSLinkerAction::~APSLinkerAction() {
    
}


bool APSLinkerAction::initWithProperties(APSDictionary *properties) {
    if(!APSAction::initWithProperties(properties))
        return false;
    
    // set targetActionIndex
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getTargetActionIndexKey());
    if (number) {
        this->setTargetActionIndex(APSNumber::indexWithNumber(number));
    }
    
    /*
    // set delay
    number = (APSNumber *)properties->getObjectForKey(kAPSLinkerAction_delayKey);
    if (number) {
        this->setDelay(number->getFloat());
    }
    */
    
    // set type
    number = (APSNumber *)properties->getObjectForKey(this->getTypeKey());
    if (number) {
        this->setType((APSLinkerType)number->getInteger());
    }
    
    // set noTriggerRunningTarget
    number = (APSNumber *)properties->getObjectForKey(this->getNoTriggerRunningTargetKey());
    if (number) {
        this->setNoTriggerRunningTarget(number->getBoolean());
    }
    
    return true;
}

void APSLinkerAction::_trigger() {
    
    if (!this->getTargetGraphic()->getNode()->getActionByTag(this->getCCAction()->getTag())) {
        this->getTargetGraphic()->runAction(this);
    }
}

/*
void APSLinkerAction::stopFunc() {
    APSAction::stopFunc();
//    m_sentCount = 0;
}
*/

void APSLinkerAction::sendLinkMessage() {
    this->sendLinkMessage(this->getParentSymbol());
}

// Sends link message.
// !!! Fixme: somehow sendLinkMessage is called twice per linker action in Cocos2D-iPhone 2.0.
void APSLinkerAction::sendLinkMessage(APSSymbol *symbol) {
    APSActionGroup *targetAction = (APSActionGroup *)this->getTargetAction();
    
    switch ((int)this->m_type) {
        case kAPSLinkerTypeTrigger:
            if (targetAction && targetAction->getEnabled()) {
                // Do not trigger if the target is running.
                if (!this->getNoTriggerRunningTarget() || !targetAction->getRunning()) {
                    targetAction->trigger();
                }
            }
            break;
        case kAPSLinkerTypeInterrupt:
            if (targetAction) {
                targetAction->interrupt();
            }
            break;
        case kAPSLinkerTypeEnable:
            if (targetAction) {
                targetAction->setEnabled(true);
            }
            break;
        case kAPSLinkerTypeDisable:
            if (targetAction) {
                targetAction->setEnabled(false);
            }
            break;
        case kAPSLinkerTypeInterruptAll:
            symbol->interruptAllActions();
            break;
        default:
            break;
    }
}

APSAction *APSLinkerAction::getTargetAction() {
    if (!m_targetAction) {
        m_targetAction = (APSAction *)this->getResource(this->m_targetActionIndex);
    }
    return m_targetAction;
}

#pragma #### Protected ####

CCFiniteTimeAction * APSLinkerAction::makeCCAction() {
    //!!! Fixme: If LinkerAction objects are created indefinetely,  the same tag could be reused.
    static int actionTagCount = 0;
    
    CCFiniteTimeAction *action = APSAction::makeCCAction();
    
    action->setTag(actionTagCount++);
    return action;
}

// Makes a CCFiniteTimeAction that runs between pre and post actions.
CCFiniteTimeAction * APSLinkerAction::makeMidCCAction(bool universal, float scale) {
#if COCOS2D_VERSION >= 0x00020000
    return CCCallFunc::create(this, callfunc_selector(APSLinkerAction::sendLinkMessage));
#else
    return CCCallFunc::actionWithTarget(this, callfunc_selector(APSLinkerAction::sendLinkMessage));
#endif//APS_SKIP
    
}

APS_END_NAMESPACE


