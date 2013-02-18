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

#include "APSAnchor.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const string &APSAnchor::getPositionKey() {
    static const string key = "position";
    return key;
}

const string &APSAnchor::getBackHandleKey() {
    static const string key = "backHandle";
    return key;
}

const string &APSAnchor::getFrontHandleKey() {
    static const string key = "frontHandle";
    return key;
}

const string &APSAnchor::getProportionKey() {
    static const string key = "proportion";
    return key;
}

APSAnchor::APSAnchor(CCPoint position, CCPoint backHandle, CCPoint frontHandle, float proportion) :
m_position(position),
m_backHandle(backHandle),
m_frontHandle(frontHandle),
m_proportion(proportion)
{
    
}

APSAnchor::APSAnchor(APSDictionary *properties) :
m_position(CCPointZero),
m_backHandle(CCPointZero),
m_frontHandle(CCPointZero),
m_proportion(1.f)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSAnchor::APSAnchor(const APSAnchor &anchor) {
    this->m_position = anchor.getPosition();
    this->m_backHandle = anchor.getBackHandle();
    this->m_frontHandle = anchor.getFrontHandle();
    this->m_proportion = anchor.getProportion();
}

APSAnchor::~APSAnchor() {
    
}


bool APSAnchor::initWithProperties(APSDictionary *properties) {
    // set position
    APSString *str = (APSString *)properties->getObjectForKey(this->getPositionKey());
    if (str) {
        this->setPosition(str->getPointValue());
    }

    /*
    APSNumber *number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_positionXKey);
    if (number) {
        this->m_position.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_positionYKey);
    if (number) {
        this->m_position.y = number->getFloat();
    }
    */
    
    // set backHandle
    str = (APSString *)properties->getObjectForKey(this->getBackHandleKey());
    if (str) {
        this->setBackHandle(str->getPointValue());
    }
    
/*
    number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_backHandleXKey);
    if (number) {
        this->m_backHandle.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_backHandleYKey);
    if (number) {
        this->m_backHandle.y = number->getFloat();
    }
    */
    
    // set frontHandle
    str = (APSString *)properties->getObjectForKey(this->getFrontHandleKey());
    if (str) {
        this->setFrontHandle(str->getPointValue());
    }
    
    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_frontHandleXKey);
    if (number) {
        this->m_frontHandle.x = number->getFloat();
    }
    number = (APSNumber *)properties->getObjectForKey(kAPSAnchor_frontHandleYKey);
    if (number) {
        this->m_frontHandle.y = number->getFloat();
    }
    */
    
    // set proportion
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getProportionKey());
    if (number) {
        this->setProportion(number->getFloat());
    }
    
    return true;
}

CCPoint APSAnchor::getPosition(float scale) {
    CCPoint p = this->getPosition();
    return CCPoint(p.x*scale, p.y*scale);
}

CCPoint APSAnchor::getBackHandle(float scale) {
    CCPoint p = this->getBackHandle();
    return CCPoint(p.x*scale, p.y*scale);
}

CCPoint APSAnchor::getFrontHandle(float scale) {
    CCPoint p = this->getFrontHandle();
    return CCPoint(p.x*scale, p.y*scale);
}


APS_END_NAMESPACE



