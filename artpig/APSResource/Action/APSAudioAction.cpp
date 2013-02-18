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

#include "APSAudioAction.h"
#include "APSAudioHolder.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSAudioAction_defaultTrimmed = false;

// const float kAPSAudioAction_defaultPlayTimeInTrack = 0.f;

const string &APSAudioAction::getTrimmedKey() {
    static const string key = "trimmed";
    return key;
}

const string &APSAudioAction::getAudioHolderCodeKey() {
    static const string key = "audioHolderCode";
    return key;
}

APSAudioAction::APSAudioAction(APSDictionary *properties) :
m_audioHolder(NULL),
m_audioHolderCode(""),
m_trimmed(kAPSAudioAction_defaultTrimmed)
// m_playTimeInTrack(kAPSAudioAction_defaultPlayTimeInTrack)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSAudioAction::~APSAudioAction() {
    
}

bool APSAudioAction::initWithProperties(APSDictionary *properties) {
    if(!APSAction::initWithProperties(properties))
        return false;
    
    // set audioHolderCode
    APSString *str = (APSString *)properties->getObjectForKey(this->getAudioHolderCodeKey());
    if (str) {
        this->setAudioHolderCode(str->c_str());
    }
    
    // set trimmed
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getTrimmedKey());
    if (number) {
        this->setTrimmed(number->getBoolean());
    }
    
    return true;
}

void APSAudioAction::preloadData() {
    APSAudioHolder *holder = this->getAudioHolder();
    if (holder) {
        holder->preloadData();
    }
}

CCFiniteTimeAction * APSAudioAction::makeMidCCAction(bool universal, float scale) {
#if COCOS2D_VERSION >= 0x00020000
    return CCSequence::create(CCCallFunc::create(this, callfunc_selector(APSAudioAction::play)), CCDelayTime::create(m_duration));
#else
    return CCSequence::actionOneTwo(CCCallFunc::actionWithTarget(this, callfunc_selector(APSAudioAction::play)), CCDelayTime::actionWithDuration(m_duration));
#endif//APS_SKIP
    }

void APSAudioAction::stopFunc() {
    if (this->getTrimmed()) {
        // Stop playing audio only if it is trimmed because playing audio may be delayed in Android.
        this->getAudioHolder()->stopForAction(this);
    }
    APSAction::stopFunc();
}

void APSAudioAction::_interrupt() {
    this->getAudioHolder()->stopForAction(this);
    APSAction::_interrupt();
}

void APSAudioAction::play() {
    this->getAudioHolder()->playForAction(this);
}

APSAudioHolder *APSAudioAction::getAudioHolder() {
    if (!m_audioHolder) {
        m_audioHolder = (APSAudioHolder *)this->getMediumForCode(this->getAudioHolderCode());
    }
    return m_audioHolder;
}

APS_END_NAMESPACE


