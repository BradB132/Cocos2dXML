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

#include "APXAnimation.h"
#include "APSSymbol.h"
#include "cocos2d.h"
#include "APSResourceManager.h"
#include "APSPlatform.h"
#include <iostream>

using namespace cocos2d;
using namespace artpig;
using namespace std;

const string kAPXAnimation_defaultSymbolTag = "Symbol1";
const string kAPXAnimation_defaultActionGroupTag = "ActionGroup1";

const string kAPXAnimation_isPlayingKey = "isPlaying";

static map<const string, set<APXAnimation *> *> _allocatedAnimations;

std::set<APXAnimation *> *animationsForProjectId(const char *pid);
void removeDataWithProjectId(const char *pid);

APXAnimation::APXAnimation(const char *projectId, bool shouldScaleModelToDevice) :
_isPlaying(false),
_symbol(NULL),
_shouldScaleModelToDevice(shouldScaleModelToDevice)
{

    APSResourceManager *manager = APSResourceManager::getResourceManagerForProjectId(projectId);
    
    if (manager) {
        _symbol = manager->newSymbol(kAPXAnimation_defaultSymbolTag.c_str());
        if (_symbol) {    
            
            if (shouldScaleModelToDevice) {
                // Scale symbol with regard to active device.
                _symbol->setScale(manager->getScaleModelToDevice(false));
            }
            
            _symbol->preloadData();
            
        }
        
    }

    animationsForProjectId(projectId)->insert(this);
}

APXAnimation::~APXAnimation() {
    set<APXAnimation *> *animations = animationsForProjectId(this->getProjectId());
    animations->erase(this);
    
    const char *pid = _symbol->getResourceManager()->getProjectId();
    
    // Deleting symbol must be done before remving project because symbol's APSSprite and APSAudioAction objects access resources to decrease reference counts.
    CC_SAFE_RELEASE_NULL(_symbol);
    
    // Clean up the project if there is no more instance.
    if (animations->size()==0) {
        removeDataWithProjectId(pid);
    }
}

/*
void APXAnimation::setScreenSize(CCSize &size) {
    APSPlatform::sharedPlatform()->setDeviceScreenSize(size);
}
*/

APXAnimation *APXAnimation::animationWithProjectId(const char *projectId, bool shouldScaleModelToDevice) {
    APXAnimation *animation = new APXAnimation(projectId, shouldScaleModelToDevice);
    animation->autorelease();
    return animation;
}

const char *APXAnimation::getProjectId() {
    APSResourceManager *rm = _symbol->getResourceManager();
    if (rm) {
        return rm->getProjectId();
    }
    return NULL;
}

cocos2d::CCLayer *APXAnimation::getRootNode() {
    return _symbol->getRootNode();
}

// Resets all CCNode objects in the symbol to become original state.
void APXAnimation::resetNodes() {
    _symbol->initNode();
}

void APXAnimation::play() {
    if (this->_hasPlayed) {
        this->resetNodes();
    }
    _symbol->triggerPrologueActionGroups();
    _hasPlayed = true;
}

void APXAnimation::stop() {
    _symbol->interruptAllActions();
}

float APXAnimation::getDuration() {
    return _symbol->getPrologueDuration();
}

bool APXAnimation::getShouldScaleModelToDevice() const {
    return _shouldScaleModelToDevice;
}

void APXAnimation::setShouldScaleModelToDevice(bool shouldScale) {
    _shouldScaleModelToDevice = shouldScale;
}

bool APXAnimation::isPlaying() {
    return _isPlaying;
}

void APXAnimation::setIsPlaying(bool isPlaying) {
    if (isPlaying) {
        _hasPlayed = true;
    }
    _isPlaying = isPlaying;
}


#pragma #### APActionGroupObserver ####

void APXAnimation::addObserver(APXAnimationObserver *observer) {
    _symbol->addActionObserver(this, kAPXAnimation_defaultActionGroupTag);

    _observers.insert(observer);
}

void APXAnimation::removeObserver(APXAnimationObserver *observer) {
    _observers.erase(observer);
}

// Notifies the observer action group specified by a tag is about to start running.
void APXAnimation::willStartAction(APSAction *action)  {
    this->setIsPlaying(true);
    for (set<APXAnimationObserver *>::iterator iter = _observers.begin(); iter != _observers.end(); iter++) {
        (*iter)->willStartAnimation(this);
    }
}

// Notifies the observer action group specified by a tag finished running.
void APXAnimation::didFinishAction(APSAction *action) {
    this->notifyObservers();
}

void APXAnimation::notifyObservers() {
    
    //CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(APXAnimation::notifyObservers), this);
    this->setIsPlaying(false);
    
    for (set<APXAnimationObserver *>::iterator iter = _observers.begin(); iter != _observers.end(); iter++) {
        (*iter)->didFinishAnimation(this);
    }
}

std::set<APXAnimation *> *animationsForProjectId(const char *pid) {
    std::set<APXAnimation *> *animations = _allocatedAnimations[pid];
    if (!animations) {
        animations = new std::set<APXAnimation *>;
        _allocatedAnimations[pid] = animations;
    }
    return animations;
}

void removeDataWithProjectId(const char *pid) {
    // Stop all animation
    std::set<APXAnimation *> *animations = animationsForProjectId(pid);
    for (set<APXAnimation *>::iterator iter = animations->begin(); iter != animations->end(); iter++) {
        (*iter)->stop();
    }
    _allocatedAnimations.erase(pid);
    
    APSResourceManager::removeResourceManagerForProjectId(pid);
}


