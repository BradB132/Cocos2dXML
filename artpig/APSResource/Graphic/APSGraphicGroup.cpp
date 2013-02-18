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

#include "APSGraphicGroup.h"
#include "APSResourceArray.h"
#include "APSSprite.h"
#include "APSGraphicAction.h"


using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const bool kAPSGraphicGroup_defaultHasAnimatableChild = false;
const unsigned int kAPSGraphicGroup_defaultDisplayedFrameIndex = 0;

const string &APSGraphicGroup::getChildIndexesKey() {
    static const string key = "childIndexes";
    return key;
}

const string &APSGraphicGroup::getHasAnimatableChildKey() {
    static const string key = "hasAnimChlid";
    return key;
}

const string &APSGraphicGroup::getDisplayedFrameIndexKey() {
    static const string key = "frameIdx";
    return key;
}


APSGraphicGroup::APSGraphicGroup(APSDictionary *properties) :
m_displayedFrameIndex(kAPSGraphicGroup_defaultDisplayedFrameIndex),
m_runningFrameIndex(kAPSGraphicGroup_defaultDisplayedFrameIndex),
m_hasAnimatableChild(kAPSGraphicGroup_defaultHasAnimatableChild)
{
    for(int i=0; i < APS_GRAPHIC_ACTION_TYPES_COUNT; i++) {
        m_runningActions[i]=NULL;
    }

    m_children = new APSResourceArray(this);
    
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSGraphicGroup::~APSGraphicGroup() {
    APS_SAFE_DELETE(m_children)
}

bool APSGraphicGroup::initWithProperties(APSDictionary *properties) {
    if(!APSGraphic::initWithProperties(properties))
        return false;
    
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getHasAnimatableChildKey());
    if (number) {
        this->setHasAnimatableChild(number->getBoolean());
    }
    
    number = (APSNumber *)properties->getObjectForKey(this->getDisplayedFrameIndexKey());
    if (number) {
        this->setDisplayedFrameIndex(number->getUnsignedInteger());
    }
    
    // set childIndexes
    APSString *indexes = (APSString *)properties->getObjectForKey(this->getChildIndexesKey());
    if (indexes) {
        indexes->getResourceArray(this->getChildren());
    }
    
    /*
    APSArray *array = (APSArray *)properties->getObjectForKey(this->getChildIndexesKey());
    if (array) {
        APSResourceArray *children = this->getChildren();
        children->reserve(array->count());
        APS_FOREACH(APSArrayStorage, *array, iter) {
            children->pushBack(APSNumber::indexWithNumber((APSNumber *)*iter));
        }
    }
    */
    return true;
}

CCNode *APSGraphicGroup::createNode() {
    CCNode *node = APSGraphic::createNode();
    
    this->getChildren()->preloadAll();
    APS_FOREACH(APSResourceArray, *this->getChildren(), iter) {
        APSGraphic *child = (APSGraphic *)iter->second;
        node->addChild(child->createNode());
    }

    return node;
}

bool APSGraphicGroup::initNode() {
    if(APSGraphic::initNode()) {  
        if (this->getHasAnimatableChild()) {
            this->setRunningFrameIndex(this->getDisplayedFrameIndex());
            this->updateChildSpriteFrames();
        }
        
        this->getChildren()->preloadAll();
        APS_FOREACH(APSResourceArray, *this->getChildren(), iter) {
            ((APSGraphic *)iter->second)->initNode();
        }
        
        /*
        unsigned int size = this->getChildren()->size();
        for (unsigned int i=0; i < size; i++) {
            APSGraphic *child = (APSGraphic *)this->getChildren()->getResourceAtIndex(i);
            if (!child || !child->initNode()) {
                APSLOG("Failed to access ArtPig resource for index %d.", this->getChildren()->getApsIndexAtIndex(i));
                return false;
            }
        }
         */
        return true;
    }
    return false;
}


APSSpriteSheetHolder *APSGraphicGroup::getFirstSpriteSheetHolder() {
    if (this->getHasAnimatableChild()) {
        this->getChildren()->preloadAll();
        APS_FOREACH(APSResourceArray, *this->getChildren(), iter) {
            APSSpriteSheetHolder *sh = ((APSSprite *)iter->second)->getSpriteSheetHolder();
            if (sh) {
                return sh;
            }
        }
    }
    return NULL;
}


void APSGraphicGroup::runAction(APSAction *action) {
    if(this->m_node) {
        this->m_node->runAction(action->getCCAction());
        
        this->setRunningAction(action);
    }
}

void APSGraphicGroup::stopAction(APSAction *action) {
    if (this->m_node) {
        
        this->m_node->stopAction(action->getCCAction());
        
        if(this->getRunningActionForType(action->getActionType())==action) {
            // Assign NULL for the type.
            this->setRunningAction(NULL, action->getActionType());
        }
    }
}

void APSGraphicGroup::updateAccOpacity() {
    APSGraphic::updateAccOpacity();
    this->getChildren()->preloadAll();
    APS_FOREACH(APSResourceArray, *this->getChildren(), iter) {
        ((APSSprite *)iter->second)->updateAccOpacity();
    }
}

void APSGraphicGroup::updateChildSpriteFrames() {
    if (this->getHasAnimatableChild()) {
        this->getChildren()->preloadAll();
        // If a child is animatable, all children are sprite.
        APS_FOREACH(APSResourceArray, *this->getChildren(), iter) {
            ((APSSprite *)iter->second)->updateSpriteFrame();
        }
    }
}

APSAction *APSGraphicGroup::getRunningActionForType(APSActionType type) const {
    int pos = this->getIndexForActionType(type);
    if (pos >= 0) {
        return this->m_runningActions[pos];
    }
    return NULL;
}

void APSGraphicGroup::setRunningAction(APSAction *action, APSActionType type) {
    if (type==kAPSActionTypeNone) {
        type = action->getActionType();
    }
    
    int pos = this->getIndexForActionType(type);
    if (pos >= 0) {
        this->m_runningActions[pos] = action;
    }
}

void APSGraphicGroup::setEnableActionForType(bool enable, APSActionType type) {
    int pos = this->getIndexForActionType(type);
    if (pos >= 0) {
        if (enable) {
            if (!this->isActionEnabledForType(type)) {
                this->m_runningActions[pos] = NULL;
            }
        } else {
            if (this->isActionEnabledForType(type)) {
                if (this->m_runningActions[pos]) {
                    // Interrupt currently running action.
                    this->m_runningActions[pos]->interrupt();
                }
                // By setting rigid action, no other actions are allowed to run in this graphic group.
                this->m_runningActions[pos] = this->getRigidAction();
            }
        }
    }
}

bool APSGraphicGroup::isActionEnabledForType(APSActionType type) const {
    int pos = this->getIndexForActionType(type);
    if (pos >= 0) {
        return this->m_runningActions[pos] != this->getRigidAction();
    }
    return true;
}

void APSGraphicGroup::setEnableAllActions(bool enable) {
    this->setEnableActionForType(enable, kAPSActionTypeMove);
    this->setEnableActionForType(enable, kAPSActionTypeRotation);
    this->setEnableActionForType(enable, kAPSActionTypeScale);
    this->setEnableActionForType(enable, kAPSActionTypeFade);
    this->setEnableActionForType(enable, kAPSActionTypeAnimate);
}

int APSGraphicGroup::getIndexForActionType(APSActionType type) {
    switch (type) {
        case kAPSActionTypeMove:
            return 0;
        case kAPSActionTypeRotation:
            return 1;
        case kAPSActionTypeScale:
            return 2;
        case kAPSActionTypeFade:
            return 3;
        case kAPSActionTypeAnimate:
            return 4;
        default:
            return -1;
    }
}

APSAction *APSGraphicGroup::getRigidAction() {
    static APSAction *action = NULL;
    if (!action) {
        action = new APSAction();
        action->setPriority(APS_MAX_PRIORITY);
    }
    return action;
}

APS_END_NAMESPACE






