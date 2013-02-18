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

#ifndef ArtPigIOS_APSGraphicGroup_h
#define ArtPigIOS_APSGraphicGroup_h

#include "APSGraphic.h"


APS_BEGIN_NAMESPACE(artpig)

class APSResourceArray;
class APSSpriteSheetHolder;

class APSGraphicGroup : public APSGraphic {
    APS_CLASS_NAME(APSGraphicGroup)
    
    APS_PROPERTY_KEY(ChildIndexes)
    
    APS_SYNTHESIZE_WITH_KEY(bool, m_hasAnimatableChild, HasAnimatableChild)
    
    APS_SYNTHESIZE_WITH_KEY(unsigned int, m_displayedFrameIndex, DisplayedFrameIndex)
    
    APS_SYNTHESIZE(unsigned int, m_runningFrameIndex, RunningFrameIndex)

public:
    APSGraphicGroup(APSDictionary *properties=NULL);
	virtual ~APSGraphicGroup();    
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    virtual bool initNode();
    
    /** Runs an action targeting to this graphic                        */
    void runAction(APSAction *action);
    
    /** Stops an action targeting to this graphic                        */
    void stopAction(APSAction *action);

    /** Updates accOpacity, accOpacity value propagates to the all descendant
     graphics. Opacities are multiplied from parent to children thoughout 
     graphics hierarchy. For performance reason, updateAccOpacity() should
     be called as minimum times as you can.
     */
    virtual void updateAccOpacity();
    
    virtual void updateChildSpriteFrames();

    APSResourceArray *getChildren() const { return m_children; }
    
    /** Searches and returns a sprite sheet holder of first found among children has
     */
    APSSpriteSheetHolder *getFirstSpriteSheetHolder();
    
    /** Returns a currently running action with a given action type. Except
     audio action, there can be only one running action for each action type in 
     a graphic.
     */
    APSAction *getRunningActionForType(APSActionType type) const;
    void setRunningAction(APSAction *action, APSActionType type=kAPSActionTypeNone);
    
    void setEnableActionForType(bool enable, APSActionType type);
    bool isActionEnabledForType(APSActionType type) const;
    
    void setEnableAllActions(bool enable);
    
protected:
    
    virtual cocos2d::CCNode *createNode();
    
    APSResourceArray *m_children;
    
    APSAction *m_runningActions[APS_GRAPHIC_ACTION_TYPES_COUNT];
    
private:
    static inline int getIndexForActionType(APSActionType type);
    static APSAction *getRigidAction();
};

APS_END_NAMESPACE
#endif
