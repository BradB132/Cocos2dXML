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

#ifndef ArtPigIOS_APSLinkerAction_h
#define ArtPigIOS_APSLinkerAction_h

#include "APSAction.h"


APS_BEGIN_NAMESPACE(artpig)

/**
 @brief	APSLinkerAction defines properties and methods to manage link messages between action groups.
 There are kinds of link messages(trigger, interrupt, interrupt all, enable, disable).
 If APSLinkerAction object's type is trigger, target action is triggered to start.
 If APSLinkerAction object's type is interrupt, target action is interrupted by linker.
 If APSLinkerAction object's type is interrupt all, all actions in parent symbol are interrupted.
 If APSLinkerAction object's type is disable, target action is disabled, and the disabled action cannot be triggered to start.
 If APSLinkerAction object's type is enable, target action is enabled so that it can be triggered.
 
 Although APSLinkerAction's targetAction does not have to be APSActionGroup object, linker action is generally used to send link messages between action groups.
 */
class APSLinkerAction : public APSAction {
    APS_CLASS_NAME(APSLinkerAction)

    /** Index of target action.                 */
    APS_SYNTHESIZE_WITH_KEY(APSIndex, m_targetActionIndex, TargetActionIndex)
    
    APS_SYNTHESIZE_WITH_KEY(APSLinkerType, m_type, Type)
    
    APS_SYNTHESIZE_WITH_KEY(bool, m_noTriggerRunningTarget, NoTriggerRunningTarget)
    
public:
    /** Constructor of APSLinkerAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSLinkerAction(APSDictionary *properties=NULL);    
    
	virtual ~APSLinkerAction();

    /** Initializes APSLinkerAction with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Sends link message.                             */
    virtual void sendLinkMessage();

    /** Returns the type of APSLinkerAction.                     */
    virtual APSActionType getActionType() const { return kAPSActionTypeLinker; }
    
    /** Returns target action linked by this action.    */
    virtual APSAction *getTargetAction();
    
    virtual void _trigger();
    
    //virtual void stopFunc();
    
protected:
    
    void sendLinkMessage(APSSymbol *symbol);
    
    /** Creates and returns an autoreleased cocos2d::CCAction object. */
    virtual cocos2d::CCFiniteTimeAction * makeCCAction();

    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    virtual cocos2d::CCFiniteTimeAction * makeMidCCAction(bool universal=false, float scale=1.0f);
    
    APSAction *m_targetAction;
    
//    int m_sentCount;
};

APS_END_NAMESPACE

#endif
