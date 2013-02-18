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

#include "APSGraphic.h"
#include "APSLinkerAction.h"
#include "APSGraphicGroup.h"
#include "APSSymbol.h"
#include "APSResourceArray.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const CCPoint kAPSGraphic_defaultAnchor = CCPoint(0.5, 0.5);
const CCPoint kAPSGraphic_defaultScale = CCPoint(1, 1);
const float kAPSGraphic_defaultRotation = 0.f;
const unsigned int kAPSGraphic_defaultOpacity = APS_MAX_OPACITY;
const bool kAPSGraphic_defaultVisible = true;
const unsigned int kAPSGraphic_defaultTouchOption = kAPSTouchOptionRetain | kAPSTouchOptionAcceptsOnlyVisible;

const string &APSGraphic::getParentIndexKey() {
    static const string key = "parentIndex";
    return key;
}

const string &APSGraphic::getTouchBeginEventLinkersKey() {
    static const string key = "TBeginLinkers";
    return key;
}

const string &APSGraphic::getTouchMovedEventLinkersKey() {
    static const string key = "TMovedLinkers";
    return key;
}

const string &APSGraphic::getTouchEndEventLinkersKey() {
    static const string key = "TEndLinkers";
    return key;
}

const string &APSGraphic::getTouchCancelledEventLinkersKey() {
    static const string key = "TCancelLinkers";
    return key;
}

const string &APSGraphic::getPositionKey() {
    static const string key = "position";
    return key;
}

const string &APSGraphic::getSizeKey() {
    static const string key = "size";
    return key;
}

const string &APSGraphic::getAnchorKey() {
    static const string key = "anchor";
    return key;
}

const string &APSGraphic::getScaleKey() {
    static const string key = "scale";
    return key;
}

const string &APSGraphic::getRotationKey() {
    static const string key = "rotation";
    return key;
}

const string &APSGraphic::getOpacityKey() {
    static const string key = "opacity";
    return key;
}

const string &APSGraphic::getVisibleKey() {
    static const string key = "visible";
    return key;
}

const string &APSGraphic::getTouchOptionKey() {
    static const string key = "touchOption";
    return key;
}

const string &APSGraphic::getLevelKey() {
    static const string key = "level";
    return key;
}

APSGraphic::APSGraphic(APSDictionary *properties) :
m_parent(NULL),
m_parentIndex(APS_NIL_INDEX),
m_node(NULL),
m_position(CCPointZero),
m_size(CCSizeZero),
m_anchor(kAPSGraphic_defaultAnchor),   
m_scale(kAPSGraphic_defaultScale), 
m_rotation(kAPSGraphic_defaultRotation),
m_opacity(kAPSGraphic_defaultOpacity),
m_level(0),
m_runningOpacity(kAPSGraphic_defaultOpacity),
m_visible(kAPSGraphic_defaultVisible),
m_touchOption(kAPSGraphic_defaultTouchOption),
m_touchEventLinkers(NULL)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSGraphic::~APSGraphic() {
    if (m_touchEventLinkers) {
        APS_FOREACH(vector<APSResourceArray *>, *m_touchEventLinkers, iter) {
            APS_SAFE_DELETE(*iter)
        }
        APS_SAFE_DELETE(m_touchEventLinkers)
    }

    CC_SAFE_RELEASE(this->m_node);
}

bool APSGraphic::initWithProperties(APSDictionary *properties) {
    if(!APSResource::initWithProperties(properties))
        return false;
    
    APSPlatform *platform = APSPlatform::sharedPlatform();
    
    // set parentIndex
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getParentIndexKey());
    if (number) {
        this->m_parentIndex = APSNumber::indexWithNumber(number);
    }
    
    // set position
    APSString *str = (APSString *)properties->getObjectForKey(this->getPositionKey());
    if (str) {
        CCPoint p = str->getPointValue();
        this->setPosition(platform->convertPointFromPixels(p));
    }
    
    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_positionXKey);
    if (number) {
        this->m_position.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_positionYKey);
    if (number) {
        this->m_position.y = number->getFloat();
    }
    */
    
    // set size
    str = (APSString *)properties->getObjectForKey(this->getSizeKey());
    if (str) {
        CCSize size = str->getSizeValue();
        this->setSize(platform->convertSizeFromPixels(size));
    }
    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_widthKey);
    if (number) {
        this->m_size.width = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_heightKey);
    if (number) {
        this->m_size.height = number->getFloat();
    }
    */
    
    // set anchor
    str = (APSString *)properties->getObjectForKey(this->getAnchorKey());
    if (str) {
        this->setAnchor(str->getPointValue());
    }

    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_anchorXKey);
    if (number) {
        this->m_anchor.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_anchorYKey);
    if (number) {
        this->m_anchor.y = number->getFloat();
    }
    */
    
    // set scale
    str = (APSString *)properties->getObjectForKey(this->getScaleKey());
    if (str) {
        this->setScale(str->getPointValue());
    }
    
    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_scaleXKey);
    if (number) {
        this->m_scale.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSGraphic_scaleYKey);
    if (number) {
        this->m_scale.y = number->getFloat();
    }
    */
    
    // set rotation
    number = (APSNumber *)properties->getObjectForKey(this->getRotationKey());
    if (number) {
        this->m_rotation = number->getFloat();
    }
    
    // set opacity
    number = (APSNumber *)properties->getObjectForKey(this->getOpacityKey());
    if (number) {
        this->m_runningOpacity = this->m_opacity = number->getUnsignedInteger();
    }
    
    
    // set visible
    number = (APSNumber *)properties->getObjectForKey(this->getVisibleKey());
    if (number) {
        this->m_visible = number->getBoolean();
    }
    
    // set touchOption
    number = (APSNumber *)properties->getObjectForKey(this->getTouchOptionKey());
    if (number) {
        this->m_touchOption = number->getUnsignedInteger();
    }
    
    // set level
    number = (APSNumber *)properties->getObjectForKey(this->getLevelKey());
    if (number) {
        this->m_level = (float)number->getFloat();
    }
    
    APSString *linkersString = (APSString *)properties->getObjectForKey(this->getTouchBeginEventLinkersKey());
    if (linkersString) {
        APSResourceArray *linkers = this->getLinkersForEventWithCreation(kAPSEventTypeTouchBegan);
        linkersString->getResourceArray(linkers);
    }
    
    linkersString = (APSString *)properties->getObjectForKey(this->getTouchMovedEventLinkersKey());
    if (linkersString) {
        APSResourceArray *linkers = this->getLinkersForEventWithCreation(kAPSEventTypeTouchMoved);
        linkersString->getResourceArray(linkers);
    }
    
    linkersString = (APSString *)properties->getObjectForKey(this->getTouchEndEventLinkersKey());
    if (linkersString) {
        APSResourceArray *linkers = this->getLinkersForEventWithCreation(kAPSEventTypeTouchEnded);
        linkersString->getResourceArray(linkers);
    }
    
    linkersString = (APSString *)properties->getObjectForKey(this->getTouchCancelledEventLinkersKey());
    if (linkersString) {
        APSResourceArray *linkers = this->getLinkersForEventWithCreation(kAPSEventTypeTouchCancelled);
        linkersString->getResourceArray(linkers);
    }
    
    return true;
}

void APSGraphic::updateAccOpacity() {
    
    APSGraphic *parent = this->getParent();
    unsigned int parentAccOpacity = parent ? parent->getAccOpacity() : APS_MAX_OPACITY;

    this->m_accOpacity = parentAccOpacity * this->m_runningOpacity / APS_MAX_OPACITY;
}

CCPoint APSGraphic::getOriginPosition() const {
    return accpSub(this->getPosition(), 
                           accpRotate(accpCompMult(CCPoint(this->getSize().width, this->getSize().height),
                                                  accpCompMult(this->getScale(), this->getAnchor()) ), this->getRotation()));
}

APSResourceArray *APSGraphic::getLinkersForEventWithCreation(APSEventType type) {
    if (!m_touchEventLinkers) {
        m_touchEventLinkers = new vector<APSResourceArray *>(4, (APSResourceArray *)NULL);
    }
    
    unsigned int pos;
    switch (type) {
        case kAPSEventTypeTouchBegan:
            pos = 0;
            break;
        case kAPSEventTypeTouchMoved:
            pos = 1;
            break;
        case kAPSEventTypeTouchEnded:
            pos = 2;
            break;
        case kAPSEventTypeTouchCancelled:
            pos = 3;
            break;
        default:
            return NULL;
    }
    
    vector<APSResourceArray *> *linkers = m_touchEventLinkers;
    if (!(*linkers)[pos]) {
        (*linkers)[pos] = new APSResourceArray(this);
    }
    return (*linkers)[pos];
}

APSResourceArray *APSGraphic::getLinkersForEvent(APSEventType type) const {
    if (!m_touchEventLinkers) {
        return NULL;
    }
    
    unsigned int pos;
    switch (type) {
        case kAPSEventTypeTouchBegan:
            pos = 0;
            break;
        case kAPSEventTypeTouchMoved:
            pos = 1;
            break;
        case kAPSEventTypeTouchEnded:
            pos = 2;
            break;
        case kAPSEventTypeTouchCancelled:
            pos = 3;
            break;
        default:
            return NULL;
    }
    
    return (*m_touchEventLinkers)[pos];
    
}

CCNode *APSGraphic::createNode() {
    if (!m_node) {
#if COCOS2D_VERSION >= 0x00020000
        m_node = CCNode::create();
#else
        m_node = CCNode::node();
#endif//APS_SKIP
        m_node->retain();
    }
    
    return m_node;
}

bool APSGraphic::initNode() {
    m_node->setPosition(this->getPosition());
    
    m_node->setContentSize(this->getSize());
    
    m_node->setAnchorPoint(this->getAnchor());
    m_node->setScaleX(this->getScale().x);
    m_node->setScaleY(this->getScale().y);
    m_node->setRotation(this->getRotation());
#if COCOS2D_VERSION >= 0x00020000
    m_node->setVisible(this->getVisible());
#else
    m_node->setIsVisible(this->getVisible());
#endif//APS_SKIP
    
 
    
    // We assume that this APSGraphic object is APSSymbol's child or symbol itself, and symbol calls updateAccOpacity() at the end of initialization. If this graphic is used solely,  updateAccOpacity() should be called for this object.
    this->m_runningOpacity = this->m_opacity;
    
    return true;
}

CCAffineTransform APSGraphic::getNodeToSymbolTransform() {
    CCNode *node = this->getNode();
    
    CCAffineTransform t = node->nodeToParentTransform();
    APSGraphic *graphic = this->getParent();
    while (graphic != this->getParentSymbol()) {
        node = graphic->getNode();
        t = CCAffineTransformConcat(t, node->nodeToParentTransform());
        
        graphic = graphic->getParent();
    }
    
    return t;
}

CCAffineTransform APSGraphic::getSymbolToNodeTransform() {
    CCNode *node = this->getNode();
    
    CGAffineTransform t = node->parentToNodeTransform();
    APSGraphic *graphic = this->getParent();
    while (graphic != this->getParentSymbol()) {
        node = graphic->getNode();
        t = CCAffineTransformConcat(node->parentToNodeTransform(), t);
        
        graphic = graphic->getParent();
    }
    
    return t;
}

CCPoint APSGraphic::convertPositionFromParentNode(const CCPoint &position) {
    return CCPointApplyAffineTransform(position, this->getNode()->parentToNodeTransform());
}

#pragma #### Accessors ####

CCNode *APSGraphic::getNode() {
    if (!this->m_node) {
        this->createNode();
        this->initNode();
    }
    return this->m_node;
}

APSGraphic *APSGraphic::getParent() {
    if (!m_parent) {
        m_parent = (APSGraphicGroup *)this->getResource(this->m_parentIndex);
    }
    return m_parent;
}

CCPoint APSGraphic::getPositionInPixels() {
    CCPoint position = this->getPosition();
    return APSPlatform::sharedPlatform()->convertPointToPixels(position);
}

CCSize APSGraphic::getSizeInPixels() {
    CCSize size = this->getSize();
    return APSPlatform::sharedPlatform()->convertSizeToPixels(size);
}

bool APSGraphic::isNodeVisible() {
    return this->getAccOpacity() > 0 &&
#if COCOS2D_VERSION >= 0x00020000
    this->getNode()->isVisible();
#else
    this->getNode()->getIsVisible();
#endif//APS_SKIP
    
}

bool APSGraphic::getRetainsTouch() const {
    return m_touchOption & kAPSTouchOptionRetain;
}

void APSGraphic::setRetainsTouch(bool retainsTouch) {
    if (retainsTouch) {
        m_touchOption |= kAPSTouchOptionRetain;
    } else {
        m_touchOption &= ~ kAPSTouchOptionRetain;
    }
}

bool APSGraphic::getAcceptsTouchMoveEnter() const {
    return m_touchOption & kAPSTouchOptionAcceptMoveEnter;
}

void APSGraphic::setAcceptsTouchMoveEnter(bool acceptsMoveEnter) {
    if (acceptsMoveEnter) {
        m_touchOption |= kAPSTouchOptionAcceptMoveEnter;
    } else {
        m_touchOption &= ~ kAPSTouchOptionAcceptMoveEnter;
    }
}

bool APSGraphic::getAcceptsTouchOnlyVisible() const {
    return m_touchOption & kAPSTouchOptionAcceptsOnlyVisible;
}

void APSGraphic::setAcceptsTouchOnlyVisible(bool acceptsTouchOnlyVisible) {
    if (acceptsTouchOnlyVisible) {
        m_touchOption |= kAPSTouchOptionAcceptsOnlyVisible;
    } else {
        m_touchOption &= ~ kAPSTouchOptionAcceptsOnlyVisible;
    }
}

APS_END_NAMESPACE

