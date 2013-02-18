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

#include "APSBezierMoveAction.h"
#include "APSGraphicGroup.h"
#include "APSCCActionInterval.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSBezierMoveAction::getAnchorsKey() {
    static const string key = "anchors";
    return key;
}

APSBezierMoveAction::APSBezierMoveAction(APSDictionary *properties)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSBezierMoveAction::~APSBezierMoveAction() {
    APS_FOREACH(vector<APSAnchor *>, this->m_anchors, iter) {
        APS_SAFE_DELETE(*iter);
    }
}

bool APSBezierMoveAction::initWithProperties(APSDictionary *properties) {
    if(!APSIntervalGraphicAction::initWithProperties(properties))
        return false;
    
    // set anchors
    APSArray *anchorsPl = (APSArray *)properties->getObjectForKey(this->getAnchorsKey());

    APS_FOREACH(APSArrayStorage, *anchorsPl, iter) {
        APSAnchor *anchor = new APSAnchor;
        anchor->initWithProperties((APSDictionary *)*iter);
        this->m_anchors.push_back(anchor);
    }
    return true;
}

void APSBezierMoveAction::saveNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        // Save the position of graphic into the first anchor's position.
        APSAnchor *anc1 = this->m_anchors[0];
        anc1->setPosition(graphic->getNode()->getPosition());
    }
}

void APSBezierMoveAction::restoreNodeState() {
    APSGraphic *graphic = this->getTargetGraphic();
    if (graphic) {
        APSAnchor *fAnchor = this->m_anchors[0];
        graphic->getNode()->setPosition(fAnchor->getPosition());
    }
}

vector<APSAnchor *> *APSBezierMoveAction::getAnchors() {
    return &this->m_anchors;
}

CCActionInterval *APSBezierMoveAction::makeGraphicCCAction(bool universal, float scale) {
    if (universal && this->isRestoringAction()) {
        APSLOG("Making general purposed action of %s failed. a repeating action with restoring graphic's state cannot be made for general purpose action.", this->getClassName().c_str());
        return NULL;
    }

    int size = this->m_anchors.size();
    
    vector<CCActionInterval *> actions;
    actions.reserve(size);
    
    ccBezierConfig config;
    CCActionInterval *action=NULL;
        
    APSAnchor *anc2 = this->m_anchors[0];
    for (int i=0; i < size-1; i++) {
        APSAnchor *anc1 = anc2;
        anc2 = this->m_anchors[i+1];
        
        config.controlPoint_1 = anc1->getFrontHandle(scale);
        config.controlPoint_2 = anc2->getBackHandle(scale);
        config.endPosition = anc2->getPosition(scale);
        if (this->getRelative()) {
            CCPoint prevPoint = anc1->getPosition(scale);
            config.controlPoint_1 = ccpSub(config.controlPoint_1, prevPoint);
            config.controlPoint_2 = ccpSub(config.controlPoint_2, prevPoint);
            config.endPosition = ccpSub(config.endPosition, prevPoint);

#if COCOS2D_VERSION >= 0x00020000
            action = CCBezierBy::create(anc1->getProportion()*this->getDuration(), config);
#else
            action = CCBezierBy::actionWithDuration(anc1->getProportion()*this->getDuration(), config);
#endif//APS_SKIP
        } else {
            action = APSCCBezierTo::actionWithDuration(anc1->getProportion()*this->getDuration(), config);                
        }
        
        actions.push_back(action);
    }
    
    if (actions.size()==1) {
        // If bezier move is single move, append null move action.
#if COCOS2D_VERSION >= 0x00020000
        actions.push_back(CCMoveBy::create(0., CCPointZero));
#else
        actions.push_back(CCMoveBy::actionWithDuration(0., CCPointZero));
#endif//APS_SKIP
    }
    
    CCActionInterval *seq = NULL;
    vector<CCActionInterval *>::reverse_iterator rit;
    vector<CCActionInterval *>::reverse_iterator rend = actions.rend();
    for ( rit=actions.rbegin() ; rit < rend; ++rit ) {
        action = *rit;
        if (!seq) {
            seq = action;
        } else if (rit+1==rend && universal && this->isRestoringAction()) {
            seq = APSCCMoveSequence::actionOneTwo(action, seq, true);
        } else {
#if COCOS2D_VERSION >= 0x00020000
            seq = CCSequence::create(action, seq);
#else
            seq = CCSequence::actionOneTwo(action, seq);
#endif//APS_SKIP
        }
    }
    
    return seq;
}

APS_END_NAMESPACE
