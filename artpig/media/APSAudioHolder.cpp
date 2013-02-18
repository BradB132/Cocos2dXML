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

#include "APSAudioHolder.h"
#include "SimpleAudioEngine.h"
#include "APSResourceManager.h"
#include "APSAudioAction.h"

using namespace CocosDenshion;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSAudioHolder::getIsBackgroundKey() {
    static const string key = "isBackground";
    return key;
}

#define APSAudioHolder_propertyInitialization \
m_runningAction(NULL),\
m_effectId(0),\
m_isBackground(false),\
m_filePath(NULL)

APSAudioHolder::APSAudioHolder(const char *code, APSResourceManager *manager) :
APSMedium(code, manager),
APSAudioHolder_propertyInitialization
{
}

APSAudioHolder::APSAudioHolder(APSDictionary *properties) :
APSAudioHolder_propertyInitialization
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSAudioHolder::~APSAudioHolder() {
    
    APS_SAFE_DELETE(m_filePath)
}

bool APSAudioHolder::initWithProperties(APSDictionary *properties) {
    if(!APSMedium::initWithProperties(properties))
        return false;
        
    // isBackground
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getIsBackgroundKey());
    if (number) {
        this->setIsBackground(number->getBoolean());
    }
    
    return true;
}

void APSAudioHolder::clearCachedData() { 
    if (!this->getRunningAction()) {
        if (this->getIsBackground()) {
        } else {
        SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
        engine->unloadEffect(this->getFilePath()->c_str());
    }
    }
     APSMedium::clearCachedData();
}

void APSAudioHolder::preloadData() {
    if (this->getIsBackground()) {
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(this->getFilePath()->c_str());
    } else {
        SimpleAudioEngine::sharedEngine()->preloadEffect(this->getFilePath()->c_str());
    }
    
}

void APSAudioHolder::playForAction(APSAction *action) {
    if (this->getRunningAction()) {
        this->stopForAction(this->getRunningAction());
    }

    if (this->getIsBackground()) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(this->getFilePath()->c_str());
    } else {
        this->setEffectId(SimpleAudioEngine::sharedEngine()->playEffect(this->getFilePath()->c_str()));
    }
    this->setRunningAction(action);
}

void APSAudioHolder::stopForAction(APSAction *action) {
    // Only the action that ran currently playing sound can stop it.
    if (this->getRunningAction()==action) {
        if (this->getIsBackground()) {
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        } else {
            SimpleAudioEngine::sharedEngine()->stopEffect(this->getEffectId());
        }
        
        this->setRunningAction(NULL);
    }
}


const string *APSAudioHolder::getFilePath() {
    if (!m_filePath) {
        m_filePath = new string(this->getResourceManager()->getPathForFilename(this->getFilename()));
    }
    return m_filePath;
}

APS_END_NAMESPACE
