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

#include "APSVisibilityAction.h"
#include "APSGraphic.h"
#include "APSGraphicGroup.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSVisibilityAction_defaultEndVisibility = true;

const string &APSVisibilityAction::getEndVisibilityKey() {
    static const string key = "endVisibility";
    return key;
}

APSVisibilityAction::APSVisibilityAction(APSDictionary *properties) :
m_endVisibility(kAPSVisibilityAction_defaultEndVisibility)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSVisibilityAction::~APSVisibilityAction() {
}

bool APSVisibilityAction::initWithProperties(APSDictionary *properties) {
    bool ok = APSInstantGraphicAction::initWithProperties(properties);
    
    // set endVisibility
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getEndVisibilityKey());
    if (number) {
        this->m_endVisibility = number->getBoolean();
    }
    
    return ok;
    
}

CCFiniteTimeAction *APSVisibilityAction::universalCCAction(float scale) {
#if COCOS2D_VERSION >= 0x00020000
    if (this->getEndVisibility()) {
        return CCShow::create();
    } else {
        return CCHide::create();
    }
#else
    if (this->getEndVisibility()) {
        return CCShow::action();
    } else {
        return CCHide::action();
    }
#endif//APS_SKIP
}

#pragma #### Protected ####

CCFiniteTimeAction * APSVisibilityAction::makeMidCCAction(bool universal, float scale) {
#if COCOS2D_VERSION >= 0x00020000
    if (m_endVisibility)
        return CCShow::create();
    else
        return CCHide::create();
#else
    if (m_endVisibility)
        return CCShow::action();
    else
        return CCHide::action();
#endif//APS_SKIP
}

APS_END_NAMESPACE
