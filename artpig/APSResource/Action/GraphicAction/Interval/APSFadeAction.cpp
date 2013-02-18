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

#include "APSFadeAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;


APS_BEGIN_NAMESPACE(artpig)


const unsigned int kAPSFadeAction_defautEndOpacity = APS_MAX_OPACITY;

const string &APSFadeAction::getEndOpacityKey() {
    static const string key = "endOpacity";
    return key;
}

APSFadeAction::APSFadeAction(APSDictionary *properties) :
m_startOpacity(APS_MAX_OPACITY),
m_endOpacity(kAPSFadeAction_defautEndOpacity)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSFadeAction::~APSFadeAction() {
}

bool APSFadeAction::initWithProperties(APSDictionary *properties) {
    if(!APSIntervalGraphicAction::initWithProperties(properties))
        return false;
    
    // set endOpacity
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getEndOpacityKey());
    if (number) {
        this->m_endOpacity = number->getUnsignedInteger();
    }
    
    return true;
    
}

#pragma #### Protected ####

CCActionInterval *APSFadeAction::makeGraphicCCAction(bool universal, float scale) {
    if (universal) {
        return APSCCFadeTo::actionWithDuration(this->getDuration(), this->getEndOpacity(), this->isRestoringAction());
    } else {
        // If universal==false, APSFadeAction manages restoring graphic states, then there is no need CCAction to restore graphic state.
        return APSCCFadeChildrenTo::actionWithDuration(this->getDuration(), this->getEndOpacity(), this->getTargetGraphic());
    }
}

void APSFadeAction::saveNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        this->m_startOpacity = graphic->getRunningOpacity();
    }
}

void APSFadeAction::restoreNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        graphic->setRunningOpacity(this->m_startOpacity);
        graphic->updateAccOpacity();
    }
}

APS_END_NAMESPACE


