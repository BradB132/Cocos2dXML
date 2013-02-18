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

#ifndef ArtPigIOS_APSGameController_h
#define ArtPigIOS_APSGameController_h

#include "APSGraphicGroup.h"
#include "APSDeviceInfo.h"
#include "APSActionObserver.h"
#include "APSTouchEventObserver.h"
#include "APSTouch.h"

APS_BEGIN_NAMESPACE(artpig)


class APSResource;
class APSAction;
class APSActionGroup;
class APSResourceProvider;
class APSNotificationCenter;
class APSArray;
class APSResourceManager;

typedef std::map<const std::string, std::set<APSActionObserver *> *> APSActionObserverTable;

extern const char *kAPSDefaultSymbolTag;
extern const char *kAPSDefaultActionGroupTag;
extern const char *kAPSAutoTriggerActionGroupTag;

/**
 @brief	APSSymbol 
 Symbol represents a character such as person or car, and it consists of many
 movable parts. Those movable parts are called graphic group because they can
 consist of several small graphics. For example, if a symbol represents person, 
 it has head, body, arms, legs, and so on. Head is composed of eyes, hair, lips,
 and so on, so we call head part a graphic group. 
 
 In addition, symbol can have actions such as walk, run, sleep, and etc. 
 In order to walk, each part(=graphic group) of a person should have individual 
 small actions, such as moving arms and legs.
 Walk action can be called action group in ArtPig system because it involves 
 several sub-actions. 
 
 APSSymbol can be created by APSResourceManager or by APSSymbol constructors.
 If APSSymbol object has any chance to access images or audio, APSSymbol object
 should be created by APSResourceManager, or resourceManager property should be
 assigned.
 */
class APSSymbol : public APSGraphicGroup {
    APS_CLASS_NAME(APSSymbol)
    /** If APSSymbol object has any chance to access images or audio,
     resourceManager property must be assigned.
     */
    APS_SYNTHESIZE(APSResourceManager *, m_resourceManager, ResourceManager)
    
    /** Background color                                            */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::ccColor4B, m_backgroundColor, BackgroundColor)
    
    /** YES if this symbol is not a child of another symbol.        */
    APS_SYNTHESIZE_WITH_KEY(bool, m_isRoot, IsRoot)
    
    APS_SYNTHESIZE_WITH_KEY(APSOrientation, m_orientation, Orientation)
    
    APS_PROPERTY_KEY(TouchBeginListeners)
    APS_PROPERTY_KEY(TouchMovedListeners)
    APS_PROPERTY_KEY(TouchEndListeners)
    APS_PROPERTY_KEY(TouchCancelledListeners)
    
    APS_SYNTHESIZE_READONLY_WITH_KEY(APSResourceArray *, m_prologues, Prologues)
    
    APS_PROPERTY_KEY(Resources)
    APS_PROPERTY_KEY(NResources)
    
public:
    /** Constructor of APSSymbol. If 'properties' parameter is not NULL, 
     instance is initialized by the properties.
     */
    APSSymbol(APSDictionary *properties=NULL);
    
    /** Constructor of APSSymbol with project id and tag.
     */
    APSSymbol(const char *projectId, const char *symbolTag=kAPSDefaultSymbolTag);
    
    virtual ~APSSymbol();

    /** Returns symbol's filename without extension with given projectId and symbolTag
     */
    static std::string getXMLFilename(const char *projectId, const char *symbolTag=kAPSDefaultSymbolTag);
    
    /** Initializes symbol with properties.                                 */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns duration of prologue action groups.                         */
    float getPrologueDuration();
    
    /** Returns a resource at a given index in resources list. If there is no 
     resource with the index, NULL is returned.
     */
    APSResource *getResourceAtIndex(APSIndex index) const;
    
    /** Triggers a given targetAction to run.                               */
    void triggerAction(APSAction *targetAction);

    /** Interrupts a given targetAction to stop                             */
    void interruptAction(APSAction *targetAction);
    
    /** Triggers all of prologue action groups. Although any action can be
     triggered by triggerAction() method, prologue action groups are assumed
     to be triggered before any other action group starts.
     */
    void triggerPrologueActionGroups();
    
    /** Triggers action group specified by a given tag.                     */
    void triggerAction(const std::string &actionTag);
        
    /** Interrupts action group specified by a given tag.                   */
    void interruptAction(const std::string &actionTag);
    
    /** Interrupts all running actions in symbol.                           */
    void interruptAllActions();
    
    /** Disables action group specified by a given tag.                     */
    void disableAction(const std::string &actionTag);

    /** Enables action group specified by a given tag.                      */
    void enableAction(const std::string &actionTag);

    /** Initializes cocos2d::CCNode objects in symbol. initNode() can be called multiple
     times to reset cocos2d::CCNode objects' states back to original.
     */
    virtual bool initNode();
    
    /** Returns a cocos2d::CCLayer object which is the root of graphics tree.        */
    virtual cocos2d::CCLayer *getRootNode();
    
    /** Returns an APSResource object for a given tag.                      */
    APSResource *getResourceForTag(const std::string &tag);

    /** Releases cached data in symbol.                                     */
    virtual void clearCachedData();
    
    /** Preloads data to perform actions without delay.                     */
    virtual void preloadData();      

    /** Returns currently running action groups                             */
    const std::set<APSActionGroup *> &getRunningActionGroups() const;
    
    /** Fills actions parameter with APSAction objects related to 
     targetGraphicTag and actionTag. The list of actions is sorted by startTime 
     APSAction property.
     */
    void getActions(std::vector<APSAction *> *actions, const std::string &targetGraphicTag, const std::string &actionGroupTag);
    
    /** Fills actions parameter with APSAction objects related to 
     targetGraphic and action. The list of actions is sorted by startTime 
     APSAction property.
     */
    void getActions(std::vector<APSAction *> *actions, APSGraphicGroup *targetGraphic, APSActionGroup *actionGroup);
    
    /** Creates an autoreleased cocos2d::CCFiniteTimeAction object, for specific target 
     graphic and action group, which is applicable to none ArtPig layer 
     structures. Target graphic and action group are identified by given 
     targetGraphicTag and actionGroupTag, respectively. 
     Position coordinates are scaled by a given scale value.
     */
    cocos2d::CCFiniteTimeAction *universalCCAction(const std::string &targetGraphicTag, const std::string &actionGroupTag, float scale=1.0f);
    
    /** Creates an autoreleased cocos2d::CCFiniteTimeAction object, for specific target 
     graphic and action group, which is applicable to none ArtPig layer 
     structures.
     Position coordinates are scaled by a given scale value.
     */
    cocos2d::CCFiniteTimeAction *universalCCAction(APSGraphicGroup *targetGraphic, APSActionGroup *actionGroup, float scale=1.0f);
    
#pragma #### Events ####
    
    void dispatchTouch(const APSTouch &touch);

#pragma #### Touch Observers ####
    
    void addTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, APSGraphic *graphic);
    
    void addTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, const std::string &graphicTag);
    
    void removeTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, APSGraphic *graphic);
    
    void removeTouchObserver(APSTouchEventObserver *observer, APSEventType eventType, const std::string &graphicTag);
    
#pragma #### Action Observers ####
    
    /** Adds an observer that implements APSActionObserver. The observer is to
     receive start & stop messages from action specified by a tag.
     */
    void addActionObserver(APSActionObserver *observer, const std::string &actionTag);
    
    /** Removes an observer that implements APSActionObserver.
     */
    void removeActionObserver(APSActionObserver *observer, const std::string &actionTag);
    
    /** Removes all observation entries for a given observer                */
    void removeActionObserver(APSActionObserver *observer);
    
    /** Removes all observation entries in symbol.                          */
    void removeAllActionObservers();
    
    /** parent graphic(APSSymbolSprite) is assigned when this symbol is used as a child of another symbol.
     */
    void setParent(APSGraphic *parent);
    
protected:
    void initialize(APSDictionary *properties=NULL);
    
    virtual cocos2d::CCNode *createNode();

    /** notifyStart() is called at the beginning of action run. 
     With calling notifyStart() and notifyStop() methods, symbol can keep track 
     of actions' activities.
     */
    void notifyStart(APSAction *action);
    
    /** notifyStop() is called when an action finishes.
     With calling notifyStart() and notifyStop() methods, symbol can keep track 
     of actions' activities.
     */
    void notifyStop(APSAction *action);
    
    APSGraphic *searchGraphic(const cocos2d::CCPoint & positionInSymbol, APSEventType type, bool filterFirstTouch=true);
        APSResourceArray *getTouchListenersForEventType(APSEventType type) const;
    APSResourceArray *getTouchListenersForEventTypeWithCreation(APSEventType type);
    
    std::set<APSActionObserver *> *getActionObservers(const std::string &tag, bool creation=false);
        float m_prologueDuration;
    std::vector<APSResource *> m_resources;
    std::set<APSActionGroup *> m_runningActionGroups;
    std::map<const std::string, APSResource *> m_taggedResources;
    
    /** a map table of observers that receive start & stop message for actions
     specified by tags.
     */
    APSActionObserverTable m_actionObservers;       
     
    std::vector<APSResourceArray *> *m_touchListeners;
    
    APSGraphic *m_firstTouchGraphic;
    APSGraphic *m_touchOwner;
        
    friend class APSAction;
    };

APS_END_NAMESPACE


typedef std::vector<std::pair<artpig::APSActionObserver *, artpig::APSAction *> > APSPendingPostStorage;
class APSCCSymbolLayer : public cocos2d::CCLayerColor {
public:
    void addFinishedActionObserver(artpig::APSActionObserver *observer, artpig::APSAction *action);
    void postAll();
protected:
    APSPendingPostStorage _finishedActions;
};
#endif
