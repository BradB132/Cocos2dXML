//
//  APSSpriteSheetHolder.cpp
//  ArtPigEditor
//
//  Created by Kim Kiyoung on 5/7/12.
//  Copyright (c) 2012 ArtPigSoft. All rights reserved.
//

#include "APSSpriteSheetHolder.h"
#include "APSResourceManager.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSSpriteSheetHolder::getFramesKey() {
    static const string key = "frames";
    return key;
}

APSSpriteSheetHolder::APSSpriteSheetHolder(const char *code, APSResourceManager *manager) :
APSImageHolder(code, manager),
m_runtimePlPath(NULL),
m_isCached(false)
{
}

APSSpriteSheetHolder::APSSpriteSheetHolder(APSDictionary *properties) :
m_runtimePlPath(NULL),
m_isCached(false)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSSpriteSheetHolder::~APSSpriteSheetHolder() {
    this->clearCachedData();
    APS_FOREACH(vector<APSSpriteFrame *>, this->m_frames, iter) {
        APS_SAFE_DELETE(*iter);
    }
}

bool APSSpriteSheetHolder::initWithProperties(APSDictionary *properties) {
    bool ok = APSImageHolder::initWithProperties(properties);
        
    APSArray *array = (APSArray *)properties->getObjectForKey(this->getFramesKey());

    if (array) {
        APS_FOREACH(APSArrayStorage, *array, iter) {
            APSSpriteFrame *frame = new APSSpriteFrame((APSDictionary *)*iter, this);
            this->m_frames.push_back(frame);
        }
    }
    
    return ok;
}

void APSSpriteSheetHolder::preloadData() {
    this->getFrames();
}

void APSSpriteSheetHolder::clearCachedData() {
    APSImageHolder::clearCachedData();
    APS_FOREACH(vector<APSSpriteFrame *>, this->m_frames, iter) {
        (*iter)->setCCSpriteFrame(NULL);
    }
    this->setIsCached(false);
}

CCSpriteFrame *APSSpriteSheetHolder::getCCSpriteFrameAtIndex(unsigned int index) {
    vector<APSSpriteFrame *> *frames = this->getFrames();
    
    unsigned int count = frames->size();
    
    if (index >= count) {
        index = count-1;
    }
    
    return frames->at(index)->getCCSpriteFrame();
}

const char *APSSpriteSheetHolder::getRuntimePlPath() {
    if (!m_runtimePlPath) {
        m_runtimePlPath = new string();
        this->getPlFilenameWithImageFilename(m_runtimePlPath, this->getRuntimeFullPath()->c_str());
    }
    return m_runtimePlPath->c_str();
}
void APSSpriteSheetHolder::getPlFilenameWithImageFilename(string *plFilename, const char *imageFile) {
    *plFilename = imageFile;
    long idx = plFilename->rfind(".");
    long size = plFilename->size();
    plFilename->replace(idx+1, size-idx-1, APSSpriteSheetHolder::getPlFileExtension());
}

vector<APSSpriteFrame *> *APSSpriteSheetHolder::getFrames(bool loadCache) {
    if (loadCache && !this->getIsCached()) {
        CCSpriteFrameCache *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        spriteFrameCache->addSpriteFramesWithFile(this->getRuntimePlPath());
        
        APS_FOREACH(vector<APSSpriteFrame *>, this->m_frames, iter) {
            (*iter)->setCCSpriteFrame(spriteFrameCache->spriteFrameByName((*iter)->getInternalName()));
        }
        this->setIsCached(true);
    }
    return &this->m_frames;
}

APS_END_NAMESPACE
