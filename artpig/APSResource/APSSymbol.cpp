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

#include "APSSymbol.h"
#include "APSActionGroup.h"
#include "APSGraphic.h"
#include "APSElements.h"
#include "APSXMLParser.h"
#include "APSAudioHolder.h"
#include "APSImageHolder.h"
#include "APSXMLParser.h"
#include "APSResourceManager.h"
#include "APSGraphicAction.h"
#include "APSLinkerAction.h"
#include "APSTouchEventNotificationLinker.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const char *kAPSDefaultSymbolTag = "Symbol1";
const char *kAPSDefaultActionGroupTag= "ActionGroup1";
const char *kAPSAutoTriggerActionGroupTag= "AutoTriggerActionGroup";

const bool kAPSSymbol_defaultIsRoot = true;

const string &APSSymbol::getBackgroundColorKey() {
    static const string key = "bgColor";
    return key;
}

const string &APSSymbol::getProloguesKey() {
    static const string key = "prologues";
    return key;
}

const string &APSSymbol::getIsRootKey() {
    static const string key = "isRoot";
    return key;
}

const string &APSSymbol::getOrientationKey() {
    static const string key = "orientation";
    return key;
}

const string &APSSymbol::getResourcesKey() {
    static const string key = "resources";
    return key;
}

const string &APSSymbol::getNResourcesKey() {
    static const string key = "nResources";
    return key;
}

const string &APSSymbol::getTouchBeginListenersKey() {
    static const string key = "tBeginLns";
    return key;
}

const string &APSSymbol::getTouchMovedListenersKey() {
    static const string key = "tMovedLns";
    return key;
}

const string &APSSymbol::getTouchEndListenersKey() {
    static const string key = "tEndLns";
    return key;
}

const string &APSSymbol::getTouchCancelledListenersKey() {
    static const string key = "tCancelLns";
    return key;
}


APSSymbol::APSSymbol(APSDictionary *properties) :
m_resourceManager(NULL),m_backgroundColor(ccc4(0.,0.,0.,0.)),
m_prologueDuration(-1),
m_touchListeners(NULL),
m_isRoot(kAPSSymbol_defaultIsRoot),
m_touchOwner(NULL)
{
    this->initialize(properties);
}

APSSymbol::APSSymbol(const char *projectId, const char *symbolTag) :
m_resourceManager(NULL),m_backgroundColor(ccc4(0.,0.,0.,0.)),
m_prologueDuration(-1),
m_touchListeners(NULL),
m_isRoot(kAPSSymbol_defaultIsRoot),
m_orientation(kAPSOrientationLandscapeRight),
m_touchOwner(NULL)
{
    this->initialize();
    
    string filename = APSSymbol::getXMLFilename(projectId, symbolTag);
    string path = APSPlatform::getResourcePathForFile(filename.c_str());
    
    APSXMLParser *parser = new APSXMLParser();
    if(parser->loadFile(path.c_str())) {
        APSDictionary *symProp = parser->getDictionary();
        if (symProp) {
            this->initWithProperties(symProp);
        }
    }
    APS_SAFE_DELETE(parser)
}

void APSSymbol::initialize(APSDictionary *properties) {
    this->setParentSymbol(this);
    
    m_index = 0;

    m_prologues = new APSResourceArray(this);
    
        
    m_resources.resize(APS_PREDEFINED_RESOURCE_INDEXES_LENGTH);
    
    // first item is reserved for this(APSSymbol)
    m_resources[kAPSSymbolIndex] = this;
        if (properties) {
        this->initWithProperties(properties);
    }

}

APSSymbol::~APSSymbol() {
    
    if (m_touchListeners) {
        APS_FOREACH(vector<APSResourceArray *>, *m_touchListeners, iter) {
            APS_SAFE_DELETE(*iter)
        }
        APS_SAFE_DELETE(m_touchListeners)
    }

    APS_SAFE_DELETE(m_prologues)
    
    this->interruptAllActions();
    this->removeAllActionObservers();
    
    bool first=true;
    APS_FOREACH(vector<APSResource *>, this->m_resources, iter) {
        if (first) {
            first=false;
        } else {
            APS_SAFE_DELETE((*iter));
        }
    }}

string APSSymbol::getXMLFilename(const char *projectId, const char *symbolTag) {
    //  projectId + "_SYM_" + symbolTag+".xml";
    string str;
    str.reserve(strlen(projectId)+strlen(symbolTag)+10);
    str.append(projectId);
    str.append("_SYM_");
    str.append(symbolTag);
    str.append(".xml");
    return str;
    
}

bool APSSymbol::initWithProperties(APSDictionary *properties) {
    bool ok = true;
        
    // set size
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getNResourcesKey());
    this->m_resources.resize(number->getUnsignedInteger());
    
    if(!APSGraphicGroup::initWithProperties(properties)) {
        return false;
    }
    
    APSString *backgroundColor = (APSString *)properties->getObjectForKey(this->getBackgroundColorKey());
    if (backgroundColor) {
        this->setBackgroundColor(backgroundColor->getColorValue());
    }
    
    number = (APSNumber *)properties->getObjectForKey(this->getIsRootKey());
    if (number) {
        this->setIsRoot(number->getBoolean());
    }

    number = (APSNumber *)properties->getObjectForKey(this->getOrientationKey());
    if (number) {
        this->setOrientation(number->getInteger());
    }

    // set resources
    APSArray *array = (APSArray *)properties->getObjectForKey(this->getResourcesKey());
    if (array) {
//        this->m_resources.reserve(array->count());
        
        bool first = true;
        APS_FOREACH(APSArrayStorage, *array, iter) {
            
            if (first) {
                // first resource item is reserved for this APSSymbol.
                first=false;
            } else {
                
                // Allocate a resource object with the class name 
                APSResource *rs = APSResourceManager::newResourceWithProperties((APSDictionary *)*iter, this);
                if (rs) {
                    
                    this->m_resources[rs->getIndex()] = rs;
                    
                    // If the resource has a tag, insert it into taggedResources table.
                    if (rs->getTag()) {
                        this->m_taggedResources[rs->getTag()] = rs;
                    }
                }
            }
        }
    } else
        ok = false;
    
    if (ok) {
        APSString *indexes = (APSString *)properties->getObjectForKey(this->getProloguesKey());
        indexes->getResourceArray(this->m_prologues);
        
        //
        // Set touch listeners
        //
        APSString *listeners = (APSString *)properties->getObjectForKey(this->getTouchBeginListenersKey());
        if (listeners) {
            listeners->getResourceArray(this->getTouchListenersForEventTypeWithCreation(kAPSEventTypeTouchBegan));
        }
        
        listeners = (APSString *)properties->getObjectForKey(this->getTouchMovedListenersKey());
        if (listeners) {
            listeners->getResourceArray(this->getTouchListenersForEventTypeWithCreation(kAPSEventTypeTouchMoved));
        }
        
        listeners = (APSString *)properties->getObjectForKey(this->getTouchEndListenersKey());
        if (listeners) {
            listeners->getResourceArray(this->getTouchListenersForEventTypeWithCreation(kAPSEventTypeTouchEnded));
        }
        
        listeners = (APSString *)properties->getObjectForKey(this->getTouchCancelledListenersKey());
        if (listeners) {
            listeners->getResourceArray(this->getTouchListenersForEventTypeWithCreation(kAPSEventTypeTouchCancelled));
        }
        
    } else {
        APSLOG("Failed initializing APSSymbol.");
    }
    
    
    return ok;
}

float APSSymbol::getPrologueDuration() {
    if (this->m_prologueDuration < 0) {
        this->m_prologueDuration = 0;
        this->getPrologues()->preloadAll();
        APS_FOREACH(APSResourceArray, *this->getPrologues(), iter) {
            this->m_prologueDuration = MAX(m_prologueDuration, ((APSActionGroup *)iter->second)->getDuration());
        }
    }
    return this->m_prologueDuration;
}

APSResource *APSSymbol::getResourceAtIndex(APSIndex index) const {

    if (this->m_resources.size() > index) {
        return this->m_resources[index];
    }
    return NULL;
}

void APSSymbol::clearCachedData() {
    APS_FOREACH(vector<APSResource *>, this->m_resources, iter) {
        if ((*iter) && (*iter)!=this) {
            (*iter)->clearCachedData();
        }
    }
}

void APSSymbol::preloadData() {
    APS_FOREACH(vector<APSResource *>, this->m_resources, iter) {
        if ((*iter) && (*iter)!=this) {
            (*iter)->preloadData();
        }
    }
}

void APSSymbol::triggerAction(APSAction *targetAction) {
    // An action can be triggered only if it is enabled.
    if (targetAction) {
        APSGraphicGroup *graphic = targetAction->getTargetGraphic();
        if (!graphic) {
            graphic=this;
        }
        
        
        bool shouldTrigger=true;
        
        if (targetAction->getEnabled()) {
            int type = targetAction->getActionType();
            if (type == kAPSActionTypeGroup) {
                // The same action group is already running, so interrupt it to restart.
                set<APSActionGroup *>::iterator it = this->m_runningActionGroups.find((APSActionGroup *)targetAction);
                if(it!=this->m_runningActionGroups.end()) {
                    targetAction->interrupt();
                }
            } else {
                APSAction *oldAction = graphic->getRunningActionForType(type);
                // If target graphic is running for an action that has higher priority than 'targetAction', then 'targetAction' cannot be triggered.
                if (oldAction) {

                    if (oldAction->getActionGroup()==targetAction->getActionGroup()) {
                        // Complete the old action.
                        oldAction->getCCAction()->update(1.f);
                    } else {
                        if(oldAction->getPriority() > targetAction->getPriority()) {
                            shouldTrigger = false;
                        } else {
                            // Before triggering, force to stop the currently running action.
                            APSActionGroup *actionGroup = oldAction->getActionGroup();
                            if (actionGroup && actionGroup->getIntact()) {
                                // If target action's group is intact, stop all actions in the group.
                                actionGroup->interrupt();
                            } else {
                                oldAction->interrupt();
                            }
                        }
                    }
                }
            }
        } else {
            shouldTrigger = false;
        }
        
        if (shouldTrigger) {
            
            targetAction->_trigger();
        } else {
            APSActionGroup *actionGroup = targetAction->getActionGroup();
            if (actionGroup) {
                if (targetAction->getEnabled() && actionGroup->getIntact()) {
                    // If target action is enabled but cannot run, all actions in the action group are interrupted.
                    actionGroup->interrupt();
                } else {
                    // Since action is never triggered, decreaseRunningActionCount should be called here.
                    actionGroup->decreaseRunningActionCount();
                }
            }
        }
    }
}

void APSSymbol::interruptAction(APSAction *targetAction) {
    targetAction->_interrupt();
}

void APSSymbol::interruptAllActions() {
    // send interrupt messages to all running actions. !!!Caution: we cannot use fast iteration because the set is chaning by interrupt actions.
    while (this->m_runningActionGroups.size() > 0) {
        this->interruptAction(*this->m_runningActionGroups.begin());
    }
    }

CCLayer *APSSymbol::getRootNode() {
    return (CCLayer *)APSGraphic::getNode();
}

APSResource *APSSymbol::getResourceForTag(const string &tag) {
    return this->m_taggedResources[tag];
}

void APSSymbol::getActions(vector<APSAction *> *actions, const string &targetGraphicTag, const string &actionGroupTag) {
    APSActionGroup *actionGroup = (APSActionGroup *)this->getResourceForTag(actionGroupTag);
    APSGraphicGroup *target = (APSGraphicGroup *)this->getResourceForTag(targetGraphicTag);
    this->getActions(actions, target, actionGroup);
}

void APSSymbol::getActions(std::vector<APSAction *> *actions, APSGraphicGroup *targetGraphic, APSActionGroup *actionGroup) {
    if (actions && actionGroup && targetGraphic) {
        actionGroup->getActionsForTargetGraphic(actions, targetGraphic);
    }
}

CCFiniteTimeAction *APSSymbol::universalCCAction(const std::string &targetGraphicTag, const std::string &actionGroupTag, float scale) {
    APSGraphicGroup *graphic = (APSGraphicGroup *)this->getResourceForTag(targetGraphicTag);
    APSActionGroup *actionGroup = (APSActionGroup *)this->getResourceForTag(actionGroupTag);
    
    return this->universalCCAction(graphic, actionGroup);
}

CCFiniteTimeAction *APSSymbol::universalCCAction(APSGraphicGroup *targetGraphic, APSActionGroup *actionGroup, float scale) {
    vector<APSAction *> actions;
    this->getActions(&actions, targetGraphic, actionGroup);
    
    bool first = true;
    CCFiniteTimeAction *spawn=NULL;
    APS_FOREACH(vector<APSAction *>, actions, iter) {
        APSGraphicAction *graphicAction = dynamic_cast<APSGraphicAction *>(*iter);
        if (graphicAction) {
            CCFiniteTimeAction *action = graphicAction->universalCCAction(scale);
            if (action) {
                if (!isZeroF(graphicAction->getStartTime())) {
#if COCOS2D_VERSION >= 0x00020000
                    action = CCSequence::create(CCDelayTime::create(graphicAction->getStartTime()), action);
#else
                    action = CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(graphicAction->getStartTime()), action);
#endif//APS_SKIP
                }
                
                if (first) {
                    spawn = action;
                    first = false;
                } else {
#if COCOS2D_VERSION >= 0x00020000
                    spawn = CCSpawn::create(spawn, action);
#else
                    spawn = CCSpawn::actionOneTwo(spawn, action);
#endif//APS_SKIP
                }
            }
        }
    }
    return spawn;
}

APSResourceArray *APSSymbol::getTouchListenersForEventType(APSEventType type) const {
    if(!m_touchListeners) {
        return NULL;
    }
    
    switch (type) {
        case kAPSEventTypeTouchBegan:
            return m_touchListeners->at(0);
        case kAPSEventTypeTouchMoved:
            return m_touchListeners->at(1);
        case kAPSEventTypeTouchEnded:
            return m_touchListeners->at(2);
        case kAPSEventTypeTouchCancelled:
            return m_touchListeners->at(3);
    }
    
    return NULL;
}

APSResourceArray *APSSymbol::getTouchListenersForEventTypeWithCreation(APSEventType type) {
    vector<APSResourceArray *> *listeners = m_touchListeners;
    
    if(!listeners) {
        listeners = m_touchListeners = new vector<APSResourceArray *>(4, (APSResourceArray *)NULL);
    }
    
    unsigned int pos;
    switch (type) {
        case kAPSEventTypeTouchBegan:
            pos=0;
            break;
        case kAPSEventTypeTouchMoved:
            pos=1;
            break;
        case kAPSEventTypeTouchEnded:
            pos=2;
            break;
        case kAPSEventTypeTouchCancelled:
            pos=3;
            break;
        default:
            return NULL;
    }
    
    if (!listeners->at(pos)) {
        (*listeners)[pos] = new APSResourceArray(this);
    }
    return listeners->at(pos);
}

APSGraphic *APSSymbol::searchGraphic(const CCPoint & positionInSymbol, APSEventType type, bool filterFirstTouch) {
    APSResourceArray *listeners = this->getTouchListenersForEventType(type);
    if (!listeners) {
        return NULL;
    }
    
    listeners->preloadAll();
    
    APS_FOREACH(APSResourceArrayStorage, *listeners, iter) {
        APSGraphic *graphic = (APSGraphic *)iter->second;
        APSResourceArray *linkers = graphic->getLinkersForEvent(type);
        if (linkers && linkers->size() > 0) {
            if (filterFirstTouch && type!=kAPSEventTypeTouchBegan && !graphic->getAcceptsTouchMoveEnter() && m_firstTouchGraphic != graphic) {
                // Graphic does not accept touches that has begun external position.
                continue;
            }
            
            if (graphic->getAcceptsTouchOnlyVisible() && !graphic->isNodeVisible()) {
                continue;
            }
            
            // Calculate if the graphic is touched.
            // CCNode *node = graphic->getNode();
            CCAffineTransform t = graphic->getSymbolToNodeTransform();
            CCPoint positionInGraphic = CCPointApplyAffineTransform(positionInSymbol, t);
            
            CCRect rect;
            rect.origin = CCPointZero;
            rect.size = graphic->getSize();
            bool containsPoint = rect.containsPoint(positionInGraphic);
            
            if (containsPoint) {
                return graphic;
            }
        }
    }
    
    return NULL;
}

void APSSymbol::dispatchTouch(const APSTouch &touch) {
    if (touch.getType()==kAPSEventTypeTouchBegan) {
        this->m_touchOwner = NULL;
    }

    APSGraphic *touchedGraphic = this->m_touchOwner;
    
    // If there is no touch owner, find new owner.
    if (!touchedGraphic) {
        CCPoint positionInSymbol = this->convertPositionFromParentNode(touch.getPosition());
        
        touchedGraphic = this->searchGraphic(positionInSymbol, touch.getType());
        
        if (touch.getType() == kAPSEventTypeTouchBegan) {
            if (touchedGraphic) {
                this->m_firstTouchGraphic = touchedGraphic;
            } else {
                // Since touched graphic for touch begin type is not found, search for the other types.
                APSGraphic *graphic = NULL;
                graphic = this->searchGraphic(positionInSymbol, kAPSEventTypeTouchMoved, false);
                if (!graphic) {
                    graphic = this->searchGraphic(positionInSymbol, kAPSEventTypeTouchEnded, false);
                    if (!graphic) {
                        graphic = this->searchGraphic(positionInSymbol, kAPSEventTypeTouchCancelled, false);
                    }
                }
                this->m_firstTouchGraphic = graphic;
            }
        }
     }

    // Touch owner has been found.
    if (touchedGraphic) {
        APSResourceArray *linkers = touchedGraphic->getLinkersForEvent(touch.getType());
        if (linkers) {
            linkers->preloadAll();
            
            // Trigger linker actions in the target graphic.
            APS_FOREACH(APSResourceArray, *linkers, iter2) {
                APSLinkerAction *action = (APSLinkerAction *)iter2->second;
                if (action->getType()==kAPSLinkerTypeNotifyEvent) {
                    // Notify touch events to the registered observers.
                    APSTouchEventNotificationLinker *notifier = (APSTouchEventNotificationLinker *)action;
                    switch (touch.getType()) {
                        case kAPSEventTypeTouchBegan:
                            notifier->getObserver()->touchBegan(touchedGraphic, touch);
                            break;
                        case kAPSEventTypeTouchMoved:
                            notifier->getObserver()->touchMoved(touchedGraphic, touch);
                            break;
                        case kAPSEventTypeTouchEnded:
                            notifier->getObserver()->touchEnded(touchedGraphic, touch);
                            break;
                        case kAPSEventTypeTouchCancelled:
                            notifier->getObserver()->touchCancelled(touchedGraphic, touch);
                            break;
                    }
                } else {
                    if (!action->getRunning()) {
                        this->triggerAction(action);
                    }
                }
            }
        }
        
        if (touch.getType()==kAPSEventTypeTouchBegan) {
            if (touchedGraphic->getRetainsTouch()) {
                this->m_touchOwner = touchedGraphic;
            } else {
                this->m_touchOwner = NULL;
            }
        }
    } else {
        this->m_touchOwner = NULL;
    }
    
    switch (touch.getType()) {
        case kAPSEventTypeTouchEnded:
        case kAPSEventTypeTouchCancelled:
            this->m_touchOwner = this->m_firstTouchGraphic = NULL;
    }
}

#pragma #### Protected ####

void APSSymbol::notifyStart(APSAction *action) {
    if (action) {
        // Notify start to observers
        const char *tag = action->getTag();
        if (*tag) {
            set<APSActionObserver *> *observers = this->getActionObservers(tag);
            if (observers) {
                APS_FOREACH(set<APSActionObserver *>, *observers, iter) {
                    (*iter)->willStartAction(action);
                }
            }
        }

        if (action->getActionType()==kAPSActionTypeGroup) {
        
            this->m_runningActionGroups.insert((APSActionGroup *)action);
        }
    }
}

void APSSymbol::notifyStop(APSAction *action) {
    if (action) {
        if (action->getActionType()==kAPSActionTypeGroup) {
            this->m_runningActionGroups.erase((APSActionGroup *)action);
        }
        
        // notify observers for 'didFinishAction'
        const char *tag = action->getTag();
        if (*tag) {
            set<APSActionObserver *> *observers = this->getActionObservers(tag);
            if (observers) {
                APS_FOREACH(set<APSActionObserver *>, *observers, iter) {
                    ((APSCCSymbolLayer *)this->m_node)->addFinishedActionObserver(*iter, action);
                    //(*iter)->didFinishAction(action);
                }
            }
        }
        
        if (action->getActionType()!=kAPSActionTypeGroup) {
            APSActionGroup *actionGroup = action->getActionGroup();
            if (actionGroup) {
                actionGroup->decreaseRunningActionCount();
            }
        }

    }
}

CCNode *APSSymbol::createNode() {
    if (!m_node) {
        /*
        if (isZeroF(this->getBackgroundColor().a)) {
            m_node = new CCLayer();
            ((CCLayer *)m_node)->init();
        } else {
         */
        m_node = new APSCCSymbolLayer();
        ((APSCCSymbolLayer *)m_node)->initWithColor(this->getBackgroundColor());
        //}
    }

    APSGraphicGroup::createNode();
    
    return m_node;
}

bool APSSymbol::initNode() {
    if(APSGraphicGroup::initNode()) {
#if COCOS2D_VERSION >= 0x00020000
        m_node->ignoreAnchorPointForPosition(false);
#else
        m_node->setIsRelativeAnchorPoint(true);
#endif//APS_SKIP
        // Update decendant graphics' opacities.
        this->updateAccOpacity();
        
        return true;
    }
    return false;
}

void APSSymbol::triggerPrologueActionGroups() {
    
    this->getPrologues()->preloadAll();
    APS_FOREACH(APSResourceArray, *this->getPrologues(), iter) {
        this->triggerAction((APSAction *)iter->second);
    }
}

void APSSymbol::triggerAction(const string &tag) {
    this->triggerAction((APSActionGroup *)this->m_taggedResources[tag]);
}

void APSSymbol::interruptAction(const string &tag) {
    this->interruptAction((APSAction *)this->m_taggedResources[tag]);
}

void APSSymbol::enableAction(const string &tag) {
    APSAction *action = (APSAction *)this->m_taggedResources[tag];
    if (action) {
        action->setEnabled(true);
    }
}

void APSSymbol::disableAction(const string &tag) {
    APSActionGroup *action = (APSActionGroup *)this->m_taggedResources[tag];
    if (action) {
        action->setEnabled(false);
    }
}

const set<APSActionGroup *> &APSSymbol::getRunningActionGroups() const {
    return this->m_runningActionGroups;
}


#pragma #### Touch Observers ####

void APSSymbol::addTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, APSGraphic *graphic) {
    // Obtain the array of linker actions to be triggered by touch event.
    APSResourceArray *linkers = graphic->getLinkersForEventWithCreation(eventType);
    
    // When the touch event occurs, linker action is triggered to notify to touch event observers.
    APSTouchEventNotificationLinker *linkerAction = new APSTouchEventNotificationLinker();
    linkerAction->setParentSymbol(this);
    linkerAction->setType(kAPSLinkerTypeNotifyEvent);
    linkerAction->setTargetActionIndex(graphic->getIndex());
    linkerAction->setObserver(observer);
    
    // Add the linker in symbol's resources.
    linkerAction->setIndex((unsigned int)this->m_resources.size());
    this->m_resources.push_back(linkerAction);
    
    // Add the linker in event array of graphic.
    linkers->pushBack(linkerAction);
    
    APSResourceArray *listeners = this->getTouchListenersForEventTypeWithCreation(eventType);
    
    // Register the graphic as a touch listener.
    if(listeners->getIndexOfApsIndex(graphic->getIndex())==APS_NIL_INDEX) {
        bool inserted=false;
        listeners->preloadAll();
        
        APS_FOREACH(APSResourceArray, *listeners, iter) {
            if (((APSGraphic *)iter->second)->isAbove(graphic)) {
                inserted=true;
                listeners->insert(iter, pair<APSIndex, APSResource *>(graphic->getIndex(), graphic));
                break;
            }
        }
        
        if (!inserted) {
            listeners->pushBack(graphic);
        }
    }
}

void APSSymbol::addTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, const std::string &graphicTag) {
    // Aquire graphic from the tag.
    APSGraphic *graphic = dynamic_cast<APSGraphic *>(this->getResourceForTag(graphicTag));
    if (graphic) {
        this->addTouchObserver(observer, eventType, graphic);
    }
}

void APSSymbol::removeTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, APSGraphic *graphic) {
    APSResourceArray *linkers = graphic->getLinkersForEvent(eventType);
    if (linkers) {
        linkers->preloadAll();
        APS_FOREACH(APSResourceArray, *linkers, iter) {
            if (((APSLinkerAction *)this->m_resources[iter->first])->getType()==kAPSLinkerTypeNotifyEvent) {
                APS_SAFE_DELETE(this->m_resources[iter->first]);
                this->m_resources[iter->first]=NULL;
            }
        }
        
        linkers->clear();
    }
}

void APSSymbol::removeTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, const std::string &graphicTag) {
    // Aquire graphic from the tag.
    APSGraphic *graphic = dynamic_cast<APSGraphic *>(this->getResourceForTag(graphicTag));
    if (graphic) {
        this->removeTouchObserver(observer, eventType, graphic);
    }
}

void APSSymbol::addActionObserver(APSActionObserver *observer, const string &actionTag) {
    if (observer) {
        this->getActionObservers(actionTag, true)->insert(observer);
    }
}

void APSSymbol::removeActionObserver(APSActionObserver *observer, const string &actionTag) {
    if (observer) {
        set<APSActionObserver *> *obserserSet = this->getActionObservers(actionTag);
        if (obserserSet) {
            obserserSet->erase(observer);
        }
    }
}

void APSSymbol::removeActionObserver(APSActionObserver *observer) {
    if (observer) {
        APS_FOREACH(APSActionObserverTable, this->m_actionObservers, iter) {
            set<APSActionObserver *> *obserserSet = iter->second;
            obserserSet->erase(observer);
        }
    }
}

void APSSymbol::removeAllActionObservers() {
    
    APS_FOREACH(APSActionObserverTable, this->m_actionObservers, mapIter) {
        delete mapIter->second;
    }
    this->m_actionObservers.clear();
}

void APSSymbol::setParent(APSGraphic *parent) {
    m_parent = parent;
}

#pragma #### Protected ####

set<APSActionObserver *> *APSSymbol::getActionObservers(const string &tag, bool createNew) {
    set<APSActionObserver *> *observers = this->m_actionObservers[tag];
    if (!observers && createNew) {
        observers = new set<APSActionObserver *>;
        this->m_actionObservers[tag] = observers;
    }
    return observers;
}

APS_END_NAMESPACE

void APSCCSymbolLayer::addFinishedActionObserver(artpig::APSActionObserver *observer, artpig::APSAction *action) {
    if (_finishedActions.size()==0) {
#if COCOS2D_VERSION >= 0x00020000
        this->runAction(CCSequence::create(CCDelayTime::create(0), CCCallFunc::create(this, callfunc_selector(APSCCSymbolLayer::postAll))));
#else
        this->runAction(CCSequence::actionOneTwo(CCDelayTime::actionWithDuration(0), CCCallFunc::actionWithTarget(this, callfunc_selector(APSCCSymbolLayer::postAll))));
#endif//APS_SKIP
    }
    _finishedActions.push_back(pair<artpig::APSActionObserver *, artpig::APSAction *>(observer, action));
}

void APSCCSymbolLayer::postAll() {
    APS_FOREACH(APSPendingPostStorage, _finishedActions, iter) {
        iter->first->didFinishAction(iter->second);
    }
    _finishedActions.clear();
}






