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

#ifndef ArtPigIOS_APSActionGroup_h
#define ArtPigIOS_APSActionGroup_h

#include "APSAction.h"
#include "APSResourceArray.h"


APS_BEGIN_NAMESPACE(artpig)

class APSActionGroupSelector;
class APSActionGroup;

/**
 @brief	APSActionGroup contains unit-actions(move, rotate, scale, fade, and so on) and manages to run them.
 */
class APSActionGroup : public APSAction  {
    APS_CLASS_NAME(APSActionGroup)
    
    APS_PROPERTY_KEY(ActionIndexes)

    /** true if action group is supposed to run first among all action groups    */
    APS_SYNTHESIZE_WITH_KEY(bool, m_prologue, Prologue)
    
    /** If intact is true, whole action group is interrupted when any action in 
     the group cannot run or is interrupted. */
    APS_SYNTHESIZE_WITH_KEY(bool, m_intact, Intact)

public:
    /** Constructor of APSActionGroup. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSActionGroup(APSDictionary *properties=NULL);
    
	virtual ~APSActionGroup();
    
    /** Initializes APSActionGroup with given properties.     */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Decreases runningActionCount by 1. stopFunc() is called when the count becomes zero.    */
    void decreaseRunningActionCount();

    virtual void _trigger();
    
    /** Stops all actions in this action group. */
    virtual void _interrupt();

    /** Returns the type of action.     */
    virtual APSActionType getActionType() const { return kAPSActionTypeGroup; };

    /** Returns an array of actions in this action group. The array is sorted by startTime property of APSAction. */
    APSResourceArray *getActions() const { return m_actions; }

    /** Fills up actions parameter so that it contains all actions targeting to targetGraphic. */
    void getActionsForTargetGraphic(std::vector<APSAction *> *actions, const APSGraphicGroup *targetGraphic) const;
    
    /** startFunc() is supposed to be called at the beggining of cocos2d::CCAction's execution 
     @warning startFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void startFunc();

    /** Notifies parent symbol to trigger targetAction.
     @warning Although notifyTrigger() is declared in public, it should be called solely by cocos2d::CCAction's execution of this action group.
     */
    void notifyTrigger(cocos2d::CCNode *sender, void *targetAction);
        
protected:

    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    virtual cocos2d::CCFiniteTimeAction * makeMidCCAction(bool universal=false, float scale=1.0f);

    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run at the end. */
    virtual cocos2d::CCFiniteTimeAction * makePostCCAction();
    
    APSResourceArray *m_actions;
    
    unsigned int m_runningActionCount;    
    
private:
    cocos2d::CCFiniteTimeAction *spawnWithActions(std::vector<std::pair<APSAction *, cocos2d::CCFiniteTimeAction *> > &actionPairs);
    std::pair<APSAction *, cocos2d::CCFiniteTimeAction *> getActionPair(int actionIndex);
    
};

APS_END_NAMESPACE

#endif
