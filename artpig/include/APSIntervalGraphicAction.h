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


#ifndef ArtPigIOS_APSIntervalGraphicAction_h
#define ArtPigIOS_APSIntervalGraphicAction_h

#include "APSGraphicAction.h"


APS_BEGIN_NAMESPACE(artpig)

/*
 @brief	APSIntervalGraphicAction class defines common properties of actions that have duration.

 - In Cocos2d, CCRepeat does not work with non-relative graphic actions(eg. cocos2d::CCMoveTo, cocos2d::CCFadeTo, cocos2d::CCScaleTo...). However, ArtPig Editor assumes that repeating non-relative graphic actions bring target graphic's state to original state and proceeds next round.
 */
class APSIntervalGraphicAction : public APSGraphicAction {
    APS_ABSTRACT_CLASS_NAME(APSIntervalGraphicAction);
    
    /** If autoReverse is true, a reversed action is performed after finishing the original action.
     */
    APS_SYNTHESIZE_WITH_KEY(bool, m_autoReverse, AutoReverse)
    
    /** Delay time before reverse action starts.
     */
    APS_SYNTHESIZE_WITH_KEY(float, m_autoReverseDelay, AutoReverseDelay)
    
    /** Action repeats as many times as size of repeat property.
     */
    APS_SYNTHESIZE_WITH_KEY(unsigned int, m_repeat, Repeat)
    
    /** Pacing of action, such as linear, ease in, ease out, and so on.
     */
    APS_SYNTHESIZE_WITH_KEY(int, m_timingMode, TimingMode)
    
    /** Parameter for timingMode. timingFactor is used for ease in/out or ease elastic in/out.
     */
    APS_SYNTHESIZE_WITH_KEY(float, m_timingFactor, TimingFactor)
    
    /** If finishRecovery is true, graphic returns to the original state instantly at the end of action.
     */
    APS_SYNTHESIZE_WITH_KEY(bool, m_finishRecovery, FinishRecovery)
    
public:
    /** Constructor of APSIntervalGraphicAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSIntervalGraphicAction(APSDictionary *properties=NULL);  
    
	virtual ~APSIntervalGraphicAction();

    /** Initializes APSIntervalGraphicAction object with a given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns startTime + duration.                           */
    virtual float getEndTime();                  

    /** Returns true if action restores to original position for each iteration.
     */
    bool isRestoringAction() const;
    
    /** Returns an autoreleased cocos2d::CCAction object that can be applied to none ArtPig projects.  
     */
    virtual cocos2d::CCFiniteTimeAction *universalCCAction(float scale=1.0f);

    /** Saves current state of target graphic.  */
    virtual void saveNodeState()=0;
    
    /** Restores saved value to target graphic.  */
    virtual void restoreNodeState()=0;

    /** startFunc() is supposed to be called at the beggining of cocos2d::CCAction's execution 
     @warning startFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void startFunc();        
    
    /** stopFunc() is supposed to be called at the end of cocos2d::CCAction's execution
     @warning stopFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void stopFunc();

protected:
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    virtual cocos2d::CCFiniteTimeAction * makeMidCCAction(bool universal=false, float scale=1.0f);
    
    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f)=0;
        
    virtual cocos2d::CCActionInterval *attachRepeat(cocos2d::CCActionInterval *action);
    
    virtual cocos2d::CCActionInterval *attachTimingMode(cocos2d::CCActionInterval *action);
    
    cocos2d::CCActionInterval *m_graphicCCAction;
};

APS_END_NAMESPACE

#endif
