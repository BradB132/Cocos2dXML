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

#ifndef ArtPigIOS_APSAction_h
#define ArtPigIOS_APSAction_h

#include "APSResource.h"


APS_BEGIN_NAMESPACE(artpig)

class APSGraphicGroup;
class APSSymbol;
class APSActionGroup;
class APSActionSelector;

/**
 @brief	APSAction defines base control flow of creating and running cocos2d actions.
 
 1. When parent symbol(APSSymbol) receives trigger message for this action, the symbol checks if there is a running action with the same actionType property and the same target graphic. If there is, symbol compares priority properties of the two actions, and one of them is interrupted.
 2. To trigger this action, parent symbol calls run() method.
 3. If cocos2d::CCAction object is not created yet, it is created by getCCAction() method.
 4. run() method calls runAction() method of target graphic, and cocos2d::CCAction begins execution.
 5. At the beginning of cocos2d::CCAction's execution, startFunc() method of APSAction is called.
 6. startFunc() calls notifyStart() of parent symbol(APSSymbol).
 7. APSAction object is added to runningActions set in symbol.
 8. At the end of cocos2d::CCAction's execution, stopFunc() method of APSAction is called.
 9. stopFunc() calls notifyStop() of parent symbol.
 10. APSAction object is removed from runningActions set in symbol.
 
 - The all APSAction objects have targetGraphic no matter they are graphic action or not. Generally none graphic action's target is parentSymbol. 
 */
class  APSAction : public APSResource
{
    APS_CLASS_NAME(APSAction)

    /** Index of target graphic. If action is not a graphic action, target is parent APSSymbol object. */
    APS_SYNTHESIZE_WITH_KEY(APSIndex, m_targetGraphicIndex, TargetGraphicIndex) 
    
    /** Index of action group containing this action. */
    APS_SYNTHESIZE_WITH_KEY(APSIndex, m_actionGroupIndex, ActionGroupIndex)    
    
    /** Priority of action.  */
    APS_SYNTHESIZE_WITH_KEY(int, m_priority, Priority)
    
    /** This action can be triggered only if 'enabled' property is true. */
    APS_SYNTHESIZE_WITH_KEY(bool, m_enabled, Enabled)
    
    /** If this action is APSActionGroup, startTime indicates starting time from page loading. If this action is an action within APSActionGroup, startTime indicates starting time from ActionGroup began. */
    APS_SYNTHESIZE_WITH_KEY(float, m_startTime, StartTime) 
    
    APS_SYNTHESIZE_WITH_KEY(float, m_duration, Duration)
    
    /** running property is true if action is currently running */
    APS_SYNTHESIZE_READONLY_WITH_KEY(bool, m_running, Running)

public:
    /** Constructor of APSAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSAction(APSDictionary *properties=NULL);
	virtual ~APSAction();
    
    /** Initializes APSAction with given properties.     */
    virtual bool initWithProperties(APSDictionary *properties);
        /** Returns the type of action.     */
    virtual APSActionType getActionType() const { return kAPSActionTypeNone; } 
        
    /** Returns the end time of action.     */
    virtual float getEndTime();                         
    
    /** Releases current cocos2d::CCAction object and creates new cocos2d::CCAction. If action is currently running, it is interrupted by this method. */
    virtual void resetCCAction();

    /** Returns a cocos2d::CCAction object corresponded by this action. When getCCAction() is called for the first time, cocos2d::CCAction object is created, and APSAction retains the object. If getCCAction() is called again, the retained cocos2d::CCAction object is returned without creation. */
    cocos2d::CCAction *getCCAction();
    
    virtual void preloadData();
    
    /** Minimizes memory usage. Espectially, retained cocos2d::CCAction object is released if the action is not running.  */
    virtual void clearCachedData();           

    /** Returns target graphic. This must be called after targetGraphicIndex is properly set.  */
    virtual APSGraphicGroup *getTargetGraphic();
    
    /** Returns APSActionGroup object contains this action. This must be called after actionGroupIndex is properly set.  */
    virtual APSActionGroup *getActionGroup();
    
    /** Returns cocos2d::CCAction object created by makeMidCCAction().           */
    //cocos2d::CCFiniteTimeAction *getMidCCAction();

    /** startFunc() is supposed to be called at the beggining of cocos2d::CCAction's execution 
     @warning startFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void startFunc();
    
    /** stopFunc() is supposed to be called at the end of cocos2d::CCAction's execution
     @warning stopFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void stopFunc();                      
    
    /** Makes APSAction to run. 
     */
    virtual void trigger();
    
    /** Forces APSAction to stop.
     */
    virtual void interrupt();

    virtual void _trigger();
    
    virtual void _interrupt();
protected:

    /** Creates and returns an autoreleased cocos2d::CCAction object. */
    virtual cocos2d::CCFiniteTimeAction * makeCCAction();
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run at the beginning. 
     */
    virtual cocos2d::CCFiniteTimeAction * makePreCCAction();
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    virtual cocos2d::CCFiniteTimeAction * makeMidCCAction(bool universal=false, float scale=1.0f) { return NULL; }
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run at the end. 
     */
    virtual cocos2d::CCFiniteTimeAction * makePostCCAction();
    
    void setRunning(bool running) { this->m_running = running; }
    
    cocos2d::CCAction *m_ccAction;
    
//    cocos2d::CCFiniteTimeAction *m_midCCAction;

    APSGraphicGroup *m_targetGraphic;
    APSActionGroup *m_actionGroup;
    };

APS_END_NAMESPACE
#endif
