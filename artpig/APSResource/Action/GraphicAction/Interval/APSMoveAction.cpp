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


#include "APSMoveAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)



const string &APSMoveAction::getEndPositionKey() {
    static const string key = "endPosition";
    return key;
}

APSMoveAction::APSMoveAction(APSDictionary *properties) :
m_startPosition(CCPointZero),
m_endPosition(CCPointZero)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSMoveAction::~APSMoveAction() {
}


bool APSMoveAction::initWithProperties(APSDictionary *properties) {
    if(!APSIntervalGraphicAction::initWithProperties(properties))
        return false;
        
    // set endPosition
    APSString *str = (APSString *)properties->getObjectForKey(this->getEndPositionKey());
    if (str) {
        this->setEndPosition(str->getPointValue());
    }
    
    /*
     v 1.0.1
    APSNumber *number = (APSNumber *)properties->getObjectForKey(kAPSMoveAction_endPositionXKey);
    if (number) {
        this->m_endPosition.x = number->getFloat();
    }
    
    number = (APSNumber *)properties->getObjectForKey(kAPSMoveAction_endPositionYKey);
    if (number) {
        this->m_endPosition.y = number->getFloat();
    }
    */
    return true;
    
}


#pragma #### Protected ####

// Saves current state of target graphic
void APSMoveAction::saveNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        CCPoint pos = graphic->getNode()->getPosition();
        this->m_startPosition = CCPoint(pos.x, pos.y);
    }
}

// Restores saved value to target graphic
void APSMoveAction::restoreNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        graphic->getNode()->setPosition(CCPoint(this->m_startPosition.x, this->m_startPosition.y));
    }
}

CCActionInterval *APSMoveAction::makeGraphicCCAction(bool universal, float scale) {
    // If universal==false, APSMoveAction manages restoring graphic states, then there is no need CCAction to restore graphic state.
    bool finishRecovery = universal && this->isRestoringAction();
    CCPoint endPosition = this->getEndPosition();
    endPosition.x *= scale;
    endPosition.y *= scale;
    
    if (this->getRelative()) {
        return APSCCMoveBy::actionWithDuration(this->getDuration(), endPosition, finishRecovery);
    } else {
        return APSCCMoveTo::actionWithDuration(this->getDuration(), endPosition, finishRecovery);
    }
}

APS_END_NAMESPACE

