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

#include "APSGraphicAction.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSGraphicAction_defaultRelative = true;


const string &APSGraphicAction::getRelativeKey() {
    static const string key = "relative";
    return key;
}

APSGraphicAction::APSGraphicAction(APSDictionary *properties) :
m_relative(kAPSGraphicAction_defaultRelative)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSGraphicAction::~APSGraphicAction() {
}

bool APSGraphicAction::isGraphicAction(APSAction *action) {
    switch (action->getActionType()) {
        case kAPSActionTypeMove:                    
        case kAPSActionTypeScale:
        case kAPSActionTypeFade:
        case kAPSActionTypeVisibility:
        case kAPSActionTypeRotation:
            return true;
    }
    return false;
}

bool APSGraphicAction::initWithProperties(APSDictionary *properties) {
    if(!APSAction::initWithProperties(properties))
        return false;
    
    APSNumber *number=NULL;
    // set relative
    number = (APSNumber *)properties->getObjectForKey(this->getRelativeKey());
    if (number) {
        this->setRelative(number->getBoolean());
    }
    
    return true;
}

CCFiniteTimeAction *APSGraphicAction::universalCCAction(float scale) {
    return this->makeMidCCAction(true, scale);
}


APS_END_NAMESPACE
