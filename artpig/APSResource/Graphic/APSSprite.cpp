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

#include "APSSprite.h"
#include "APSSpriteSheetHolder.h"
#include "APSDeviceInfo.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const bool kAPSSprite_defaultIsAnimatable = false;
const bool kAPSSprite_defaultFlipX = false;
const bool kAPSSprite_defaultFlipY = false;

const string &APSSprite::getFlipXKey() {
    static const string key = "flipX";
    return key;
}

const string &APSSprite::getIsAnimatableKey() {
    static const string key = "isAnimatable";
    return key;
}

const string &APSSprite::getFlipYKey() {
    static const string key = "flipY";
    return key;
}

const string &APSSprite::getImageHolderCodeKey() {
    static const string key = "imageHolderCode";
    return key;
}

APSSprite::APSSprite(APSDictionary *properties) :
m_isAnimatable(kAPSSprite_defaultIsAnimatable),
m_imageHolder(NULL),
m_flipX(kAPSSprite_defaultFlipX),
m_flipY(kAPSSprite_defaultFlipY),
m_spriteNode(NULL)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSSprite::~APSSprite() {
    CC_SAFE_RELEASE(m_spriteNode);
}

bool APSSprite::initWithProperties(APSDictionary *properties) {
    bool ok = APSGraphic::initWithProperties(properties);
    
    APSNumber *number;
    
    // set isAnimatable
    number = (APSNumber *)properties->getObjectForKey(this->getIsAnimatableKey());
    if (number) {
        this->setIsAnimatable(number->getBoolean());
    }
    
    // set flipX
    number = (APSNumber *)properties->getObjectForKey(this->getFlipXKey());
    if (number) {
        this->setFlipX(number->getBoolean());
    }
    
    // set flipY
    number = (APSNumber *)properties->getObjectForKey(this->getFlipYKey());
    if (number) {
        this->setFlipY(number->getBoolean());
    }
    
    // set imageHolderCode
    APSString *str = (APSString *)properties->getObjectForKey(this->getImageHolderCodeKey());
    if (str) {
        this->setImageHolderCode(str->c_str());
    }
    
    /*
    // set originalFrame
    number = (APSNumber *)properties->getObjectForKey(kAPSSprite_originalFrameKey);
    if (number) {
        this->setOriginalFrame(number->getUnsignedInteger());
    }
    */
    
    return ok;
}

void APSSprite::updateAccOpacity() {
    APSGraphic::updateAccOpacity();
    if (this->m_spriteNode) {
        this->m_spriteNode->setOpacity(this->m_accOpacity);
    }
}

APSImageHolder *APSSprite::getImageHolder() {
    if (!m_imageHolder) {
        m_imageHolder = (APSImageHolder *)this->getMediumForCode(this->getImageHolderCode());
    }
    return m_imageHolder;
}

APSSpriteSheetHolder *APSSprite::getSpriteSheetHolder() {
    if (this->getIsAnimatable()) {
        return (APSSpriteSheetHolder *)this->getImageHolder();
    }
    return NULL;
}

CCPoint APSSprite::getPositionInSymbol() {
    APSGraphic *parent = this->getParent();
    if (parent) {
        return accpAdd(parent->getOriginPosition(), 
                               accpCompMult(accpRotate(this->getPosition(), parent->getRotation()), parent->getScale()));
    }
    return this->getPosition();
}

void APSSprite::assignSpriteProperties(CCSprite *sprite, float scale) {    
  
    CCSize scaledSize = accsMult(this->getSize(), scale);
    
    sprite->setRotation(this->getRotation());
    
#if COCOS2D_VERSION >= 0x00020000
    sprite->setVisible(this->getVisible());
#else
    sprite->setIsVisible(this->getVisible());
#endif//APS_SKIP
    
    sprite->setFlipX(this->getFlipX());
    sprite->setFlipY(this->getFlipY());
    
    CCSize size = sprite->getContentSize();
    sprite->setScaleX(scaledSize.width/size.width);
    sprite->setScaleY(scaledSize.height/size.height);
    
    APSGraphic *parent = this->getParent();
    
    // Flatten hierarchy.
    if (parent) {
        // Calculate vector from sprite position to parent position.
        CCPoint vPositions = accpRotate(accpSub(parent->getPosition(), this->getPositionInSymbol()), this->getRotation()*M_PI/180.f);
    
        // Calculate anchor
        CCPoint anchor = CCPoint(0.5+vPositions.x/this->getSize().width, 0.5+vPositions.y/this->getSize().height);
        
        sprite->setOpacity(parent->getOpacity());
        
        sprite->setAnchorPoint(anchor);
        
        sprite->setPosition(accpMult(parent->getPosition(), scale));
    }

}

CCNode *APSSprite::createNode() {
    CCNode *node = APSGraphic::createNode();
    APSImageHolder *ih = this->getImageHolder();
    CCSize contentSize;
    CCSize targetSize = APSPlatform::sharedPlatform()->convertSizeToPixels(this->getSize());
    
    if (ih) {
        this->m_spriteNode = new CCSprite;
        if (this->getIsAnimatable()) {
            // Create animation sprite
            APSSpriteSheetHolder *sh = (APSSpriteSheetHolder *)ih;
            CCSpriteFrame *spriteFrame = sh->getCCSpriteFrameAtIndex(((APSGraphicGroup *)this->getParent())->getDisplayedFrameIndex());
            
#if COCOS2D_VERSION >= 0x00020000
            CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::createWithTexture(ih->getTexture(), sh->getCount());
#else
            CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::batchNodeWithTexture(ih->getTexture(), sh->getCount());
#endif//APS_SKIP
            this->m_node->addChild(spriteSheet);
            
            this->m_spriteNode->initWithSpriteFrame(spriteFrame);
            spriteSheet->addChild(this->m_spriteNode);
            
            CCSize size = this->m_spriteNode->getContentSize();
            contentSize = APSPlatform::sharedPlatform()->convertSizeToPixels(size);
            
        } else {
            // Check if there is a sprite frame in sprite frame cache.
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(this->getImageHolder()->getRuntimeFilename().c_str());
            if (frame) {
                // Use the sprite frame
                this->m_spriteNode->initWithSpriteFrame(frame);
                contentSize = frame->getOriginalSizeInPixels();
                node->addChild(this->m_spriteNode);
            } else {
                // Normal sprite
                this->m_spriteNode->initWithTexture(ih->getTexture());
                contentSize = ih->getTexture()->getContentSizeInPixels();
                node->addChild(this->m_spriteNode);
            }
        }
        
        // scale the sprite to match the sizes of texture and sprite
        this->m_spriteNode->setScaleX(targetSize.width/contentSize.width);
        this->m_spriteNode->setScaleY(targetSize.height/contentSize.height);
    }

    return node;
}

bool APSSprite::initNode() {
    if(APSGraphic::initNode()) {
        CCSprite *sprite = this->m_spriteNode;
        if (sprite) {
            sprite->setAnchorPoint(CCPointZero);
            sprite->setPosition(CCPointZero);
            sprite->setFlipX(this->m_flipX);
            sprite->setFlipY(this->m_flipY);
        }
        
        return true;
    } else
        return false;
}

void APSSprite::updateSpriteFrame() {
    if (this->getIsAnimatable()) {
        APSSpriteSheetHolder *sh = this->getSpriteSheetHolder();
        if (sh) {
            CCSpriteFrame *frame = sh->getCCSpriteFrameAtIndex(((APSGraphicGroup *)this->getParent())->getRunningFrameIndex());
            if (frame) {
                if (!this->m_spriteNode->isFrameDisplayed(frame)) {
                    this->m_spriteNode->setDisplayFrame(frame);
                }
            }
        }
    }
}

APS_END_NAMESPACE
