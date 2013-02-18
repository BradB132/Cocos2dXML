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

#include "APSAnimateAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"
#include "APSSpriteSheetHolder.h"
#include "APSSpriteFrame.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const bool kAPSAnimateAction_defaultIsWholeRange = false;

const float kAPSAnimateAction_defaultInterval = 0.1f;

const string &APSAnimateAction::getIsWholeRangeKey() {
    static const string key = "wholeRange";
    return key;
}

const string &APSAnimateAction::getIntervalKey() {
    static const string key = "interval";
    return key;
}

APSAnimateAction::APSAnimateAction(APSDictionary *properties) :
m_isWholeRange(kAPSAnimateAction_defaultIsWholeRange),
m_interval(kAPSAnimateAction_defaultInterval)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSAnimateAction::~APSAnimateAction() {
}

bool APSAnimateAction::initWithProperties(APSDictionary *properties) {
    bool ok = APSIntervalGraphicAction::initWithProperties(properties);
    
    // set wholeRange
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getIsWholeRangeKey());
    if (number) {
        this->m_isWholeRange = number->getBoolean();
    }
    
    // set interval
    number = (APSNumber *)properties->getObjectForKey(this->getIntervalKey());
    if (number) {
        this->m_interval = number->getFloat();
    }
        
    return ok;
}

#pragma #### Protected ####

void APSAnimateAction::saveNodeState() {
    
    APSGraphicGroup *graphic = (APSGraphicGroup *)this->getTargetGraphic();
    if (graphic) {
        this->m_startFrameIndex = graphic->getRunningFrameIndex();
    }

}

void APSAnimateAction::restoreNodeState() {
    APSGraphicGroup *graphic = (APSGraphicGroup *)this->getTargetGraphic();
    if (graphic) {
        graphic->setRunningFrameIndex(this->m_startFrameIndex);
        graphic->updateChildSpriteFrames();
    }

}

CCActionInterval *APSAnimateAction::makeGraphicCCAction(bool universal, float scale) {
    APSGraphicGroup *graphic = (APSGraphicGroup *)this->getTargetGraphic();
    if (graphic) {
        APSSpriteSheetHolder *sh = graphic->getFirstSpriteSheetHolder();
        if (sh) {
            unsigned int count = sh->getCount();

            if (universal) {
#if COCOS2D_VERSION >= 0x00020000
                CCArray *frames = CCArray::create();
#else
                CCMutableArray<CCSpriteFrame *> *frames = CCMutableArray<CCSpriteFrame *>::arrayWithObjects(NULL);
#endif//APS_SKIP
                for (unsigned int i=0; i < count; i++) {
                    vector<APSSpriteFrame *> *apsFrames = sh->getFrames(false);
                    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(apsFrames->at(i)->getName()));
                }
                
#if COCOS2D_VERSION >= 0x00020000
                CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames);
#else
                CCAnimation *animation = CCAnimation::animationWithFrames(frames);
#endif//APS_SKIP
                
                if (this->getIsWholeRange()) {
#if COCOS2D_VERSION >= 0x00020000
                    animation->setRestoreOriginalFrame(this->isRestoringAction());
                    return CCAnimate::create(animation);
#else
                    return CCAnimate::actionWithDuration(this->getDuration(), animation, this->isRestoringAction());
#endif//APS_SKIP
                } else {
                    return APSCCAnimate::actionWithDuration(this->getDuration(), animation, this->isRestoringAction(), this->getInterval());
                }
            } else {
                if (this->getIsWholeRange()) {
                    return APSCCAnimateChildren::actionWithDuration(this->getDuration(), sh->getCount(), graphic);
                } else {
                    return APSCCAnimateChildren::actionWithDuration(this->getDuration(), sh->getCount(), graphic, this->getInterval());
                }
            }
        }
    }
    return NULL;
}

APS_END_NAMESPACE
