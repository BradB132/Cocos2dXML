//
//  APSSpriteFrame.cpp
//  ArtPigEditor
//
//  Created by Kim Kiyoung on 5/7/12.
//  Copyright (c) 2012 ArtPigSoft. All rights reserved.
//

#include "APSSpriteFrame.h"
#include "APSSpriteSheetHolder.h"


APS_BEGIN_NAMESPACE(artpig)

using namespace cocos2d;
using namespace std;

const string &APSSpriteFrame::getNameKey() {
    static const string key = "name";
    return key;
}

const string &APSSpriteFrame::getFrameIndexKey() {
    static const string key = "frameIndex";
    return key;
}

const string &APSSpriteFrame::getInternalNameKey() {
    static const string key = "itnName";
    return key;
}

APSSpriteFrame::APSSpriteFrame() :
m_ccSpriteFrame(NULL),
m_spriteSheetHolder(NULL),
m_frameIndex(0)
{
}

APSSpriteFrame::APSSpriteFrame(APSDictionary *properties, APSSpriteSheetHolder *sprietSheetHolder) :
m_ccSpriteFrame(NULL),
m_spriteSheetHolder(sprietSheetHolder),
m_frameIndex(0)
{
    // Set name
    APSString *string = (APSString *)properties->getObjectForKey(this->getNameKey());
    if (string) {
        this->setName(string->c_str());
    }
    
    // Set internalName
    string = (APSString *)properties->getObjectForKey(this->getInternalNameKey());
    if (string) {
        this->setInternalName(string->c_str());
    }
    
    // Set frameIndex
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getFrameIndexKey());
    if (number) {
        this->setFrameIndex(number->getUnsignedInteger());
    }
}

APSSpriteFrame::~APSSpriteFrame() {
}

APS_END_NAMESPACE
