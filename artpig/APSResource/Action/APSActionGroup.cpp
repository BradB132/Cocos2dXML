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

#include "APSActionGroup.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const bool kAPSActionGroup_defaultPrologue = false;
const bool kAPSActionGroup_defaultIntact = false;


const string &APSActionGroup::getActionIndexesKey() {
    static const string key = "actionIndexes";
    return key;
}

const string &APSActionGroup::getPrologueKey() {
    static const string key = "prologue";
    return key;
}

const string &APSActionGroup::getIntactKey() {
    static const string key = "intact";
    return key;
}

APSActionGroup::APSActionGroup(APSDictionary *properties) :
m_prologue(kAPSActionGroup_defaultPrologue),
m_intact(kAPSActionGroup_defaultIntact),
m_runningActionCount(0)
{
    m_actions = new APSResourceArray(this);
    
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSActionGroup::~APSActionGroup() {
    APS_SAFE_DELETE(m_actions)
}

void APSActionGroup::decreaseRunningActionCount() {
    this->m_runningActionCount--;
    if (this->m_runningActionCount == 0) {
        this->stopFunc();
    }
}

bool APSActionGroup::initWithProperties(APSDictionary *properties) {
    if(!APSAction::initWithProperties(properties))
        return false;
    
    // set prologue
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getPrologueKey());
    if (number) {
        this->setPrologue(number->getBoolean());
    }
    
    // set intact
    number = (APSNumber *)properties->getObjectForKey(this->getIntactKey());
    if (number) {
        this->setIntact(number->getBoolean());
    }
    
    // set actionIndexes
    APSString *indexes = (APSString *)properties->getObjectForKey(this->getActionIndexesKey());
    indexes->getResourceArray(this->getActions());
    
    /*
    APSArray *array = (APSArray *)properties->getObjectForKey(this->getActionIndexesKey());
    if (array) {
        unsigned int size = array->count();
        APSResourceArray *actions = this->getActions();
        if (size > actions->capacity()) {
            actions->reserve(size);
        }
        for (unsigned int i=0; i < size; i++) {
            actions->pushBack(APSNumber::indexWithNumber((APSNumber *)array->getObjectAtIndex(i)));
        }
    }
    */
    return true;
}

void APSActionGroup::getActionsForTargetGraphic(vector<APSAction *> *actions, const APSGraphicGroup *targetGraphic) const {
    if (actions && targetGraphic) {
        this->getActions()->preloadAll();
        APS_FOREACH(APSResourceArray, *this->getActions(), iter) {
            APSAction *act = (APSAction *)iter->second;
            if (act && act->getTargetGraphic()==targetGraphic) {
                actions->push_back(act);
            }
        }
        
    }
}

void APSActionGroup::startFunc() {
    // runningActionCount begins with whole actions count, and it is reduced on every sub-action finishing.
    this->m_runningActionCount = this->getActions()->size();
    
    APSAction::startFunc();
    
    // If there is no action to run, stop action group immediately.
    if (this->m_runningActionCount==0) {
        this->stopFunc();
    }
}

void APSActionGroup::_interrupt() {
    // interrupt all sub-actions.
    APSResourceArray *actions = this->getActions();
    actions->preloadAll();
    APS_FOREACH(APSResourceArray, *actions, iter) {
        APSAction *action = (APSAction *)iter->second;
        if (action->getRunning()) {
            action->interrupt();
        }
    }
    
    APSAction::_interrupt();
}

void APSActionGroup::_trigger() {
    // !!! Fixme: sometimes target node has this action group as running action even when running==NO
    this->getTargetGraphic()->stopAction(this);
    
    APSAction::_trigger();
}

CCFiniteTimeAction * APSActionGroup::makeMidCCAction(bool universal, float scale) {

    /*
     Group actions with startTime property.
     */
    int cnt = this->getActions()->size();
    if (cnt > 0) {
        vector<vector<pair<APSAction *, CCFiniteTimeAction *> > *> actionPairs;
        
        vector<pair<APSAction *, CCFiniteTimeAction *> > *pairs=NULL;
        
        float startTime = -1.f;
        for (int i=0; i < cnt; i++) {
            pair<APSAction *, CCFiniteTimeAction *> aPair = this->getActionPair(i);
            if (aPair.first && aPair.second) {
                // if next action does not start at the same time as previous action's start time, create a new pairs list.
                if (!isZeroF(aPair.first->getStartTime()-startTime)) {
                    if (pairs) {
                        actionPairs.push_back(pairs);
                    }
                    pairs = new vector<pair<APSAction *, CCFiniteTimeAction *> >;
                    startTime = aPair.first->getStartTime();
                }
                
                pairs->push_back(aPair);
            }
        }
        
        actionPairs.push_back(pairs);
        
        startTime = (*actionPairs[0])[0].first->getStartTime();
        
#if COCOS2D_VERSION >= 0x00020000
        CCFiniteTimeAction *action = CCSequence::createWithTwoActions(CCDelayTime::create(startTime), this->spawnWithActions(*actionPairs[0]));
#else
        CCFiniteTimeAction *action = CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(startTime), this->spawnWithActions(*actionPairs[0]));
#endif//APS_SKIP
                
        for (int i=1; i < actionPairs.size(); i++) {
            float nextStartTime = (*actionPairs[i])[0].first->getStartTime();
            float duration = nextStartTime - startTime;
            startTime = nextStartTime;
#if COCOS2D_VERSION >= 0x00020000
            action  = CCSequence::create(action, CCDelayTime::create(duration), this->spawnWithActions(*actionPairs[i]), NULL);
#else
            action  = CCSequence::actions(action, CCDelayTime::actionWithDuration(duration), this->spawnWithActions(*actionPairs[i]), NULL);
#endif//APS_SKIP
                    }
        
        // deallocate actionPairs
        for (int i=0; i < actionPairs.size(); i++) {
            delete actionPairs[i];
        }
        
        return action;
    }
    
    return NULL;
}

CCFiniteTimeAction * APSActionGroup::makePostCCAction() {
    // Although this CCMoveBy action does nothing, sequence of sub-actions in action goup works properly when the action group does not have any graphic action.
#if COCOS2D_VERSION >= 0x00020000
    return CCMoveBy::create(FLT_EPSILON, CCPointZero);
#else
    return CCMoveBy::actionWithDuration(FLT_EPSILON, CCPointZero);
#endif//APS_SKIP
    }

CCFiniteTimeAction *APSActionGroup::spawnWithActions(vector<pair<APSAction *, CCFiniteTimeAction *> > &actionPairs) {
    int size = actionPairs.size();
    CCFiniteTimeAction *action = actionPairs[0].second;
    
    for (int i=1; i < size; i++) {
#if COCOS2D_VERSION >= 0x00020000
        action = CCSpawn::createWithTwoActions(action, actionPairs[i].second);
#else
        action = CCSpawn::actionOneTwo(action, actionPairs[i].second);
#endif//APS_SKIP
            }
    return action;
}

pair<APSAction *, CCFiniteTimeAction *> APSActionGroup::getActionPair(int index) {
    APSAction *action = (APSAction *)this->getActions()->getResourceAtIndex(index);

    CCFiniteTimeAction *ccAction=NULL;
    if (action) {
#if COCOS2D_VERSION >= 0x00020000
        ccAction = CCCallFuncND::create(this, callfuncND_selector(APSActionGroup::notifyTrigger), action);
#else
        ccAction = CCCallFuncND::actionWithTarget(this, callfuncND_selector(APSActionGroup::notifyTrigger), action);
#endif//APS_SKIP
            }
    if (!action || !ccAction) {
        APSLOG("Failed to create action for action index %d.", this->getActions()->getApsIndexAtIndex(index));
    }
    return pair<APSAction *, CCFiniteTimeAction *>(action, ccAction);
}

void APSActionGroup::notifyTrigger(CCNode *sender, void *targetAction) {
    APSSymbol *symbol = this->getParentSymbol();
    if (symbol) {
        symbol->triggerAction((APSAction *) targetAction);
    }
}

APS_END_NAMESPACE


