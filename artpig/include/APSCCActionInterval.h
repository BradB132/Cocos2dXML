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

#ifndef ArtPigIOS_APSActionInterval_h
#define ArtPigIOS_APSActionInterval_h

#include "APSGraphic.h"

APS_BEGIN_NAMESPACE(artpig)

/** @brief APSCCFadeChildrenTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance.
 
 Instead of changing CCRGBAProtocol's opacity directly, APSCCFadeChildrenTo 
 updates target APSGraphic object's runningOpacity property. Eventually 
 updateAccOpacity() of target APSGraphic is called, and the graphic's opacity 
 propagates to all descendants by multiplying opacities. During the propagation, 
 if a child's cocos2d::CCNode implements CCRGBAProtocol, the cocos2d::CCNode object's opacity is 
 updated.
 */
class APSCCFadeChildrenTo : public cocos2d::CCActionInterval {
    APS_SYNTHESIZE(APSGraphic *, m_targetGraphic, TargetGraphic)
    APS_SYNTHESIZE(GLubyte, m_toOpacity, ToOpacity)
    APS_SYNTHESIZE(GLubyte, m_fromOpacity, FromOpacity)

public:
    APSCCFadeChildrenTo();
    virtual ~APSCCFadeChildrenTo();
    
	/** initializes the action with duration and opacity */
	bool initWithDuration(float duration, GLubyte opacity, APSGraphic *targetGraphic);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
	virtual void startWithTarget(cocos2d::CCNode *node=NULL);
	virtual void update(float time);

    virtual cocos2d::CCActionInterval *reverse();
    
	/** creates an action with duration and opacity */
	static APSCCFadeChildrenTo* actionWithDuration(float duration, GLubyte opacity, APSGraphic *targetGraphic);
protected:
    APSCCFadeChildrenTo *m_reverseAction;
};

/** @brief APSCCFadeTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance. 
 
 */
class APSCCFadeTo : public cocos2d::CCFadeTo  {
public:
    APSCCFadeTo();
    virtual ~APSCCFadeTo();
    
    static APSCCFadeTo *actionWithDuration(float duration, GLubyte opacity, bool finishRecovery=false);
    
	/** initializes the action with duration, opacity, and finishRecovery */
	bool initWithDuration(float duration, GLubyte opacity, bool finishRecovery=false);
	
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

    virtual void startWithTarget(cocos2d::CCNode *node=NULL);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    APSCCFadeTo *m_reverseAction;
    bool m_finishRecovery;
    
};
/** @brief APSCCMoveTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance. 
 
 */
class APSCCMoveTo : public cocos2d::CCMoveTo  {
public:
    APSCCMoveTo();
    virtual ~APSCCMoveTo();
    
    static APSCCMoveTo *actionWithDuration(float duration, const cocos2d::CCPoint& position, bool finishRecovery=false);
    
	/** initializes the action with duration, position, and finishRecovery */
	bool initWithDuration(float duration, const cocos2d::CCPoint& position, bool finishRecovery=false);

	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

	virtual void startWithTarget(cocos2d::CCNode *node=NULL);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    APSCCMoveTo *m_reverseAction;
    bool m_finishRecovery;
};
/** @brief APSCCMoveBy allows finishRecovery property
 */
class APSCCMoveBy : public cocos2d::CCMoveBy {
public:
    APSCCMoveBy();
    virtual ~APSCCMoveBy();
    
    static APSCCMoveBy *actionWithDuration(float duration, const cocos2d::CCPoint& position, bool finishRecovery=false);

	/** initializes the action */
	bool initWithDuration(float duration, const cocos2d::CCPoint& position, bool finishRecovery=false);

	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() { return m_finishRecovery; }
    
protected:
    bool m_finishRecovery;
};
/** @brief APSCCBezierTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance. 
 
 */
class APSCCBezierTo : public cocos2d::CCBezierTo  {
public:
    APSCCBezierTo();
    virtual ~APSCCBezierTo();
    
    static APSCCBezierTo *actionWithDuration(float duration, const cocos2d::ccBezierConfig& c, bool finishRecovery=false);
    
    virtual bool initWithDuration(float duration, const cocos2d::ccBezierConfig& c, bool finishRecovery=false);
	
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

    virtual void startWithTarget(cocos2d::CCNode *node=NULL);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
//    cocos2d::CCPoint getEndPosition() const { return m_sConfig.endPosition; }
//    void setEndPosition(cocos2d::CCPoint position) { this->m_sConfig.endPosition = position; }

    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    APSCCBezierTo *m_reverseAction;
    bool m_finishRecovery;
};

/** @brief APSCCBezierBy allows finishRecovery property
 */
class APSCCBezierBy : public cocos2d::CCBezierBy {
    APSCCBezierBy();
    virtual ~APSCCBezierBy();
    
    static APSCCBezierBy *actionWithDuration(float duration, const cocos2d::ccBezierConfig& c, bool finishRecovery=false);
    
	/** initializes the action */
	bool initWithDuration(float duration, const cocos2d::ccBezierConfig& c, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() { return m_finishRecovery; }
    
protected:
    bool m_finishRecovery;
};
/** @brief APSCCMoveSequence inherits from cocos2d::CCSequence and allows finishRecovery property
 */
class APSCCMoveSequence : public cocos2d::CCSequence {
public:
    APSCCMoveSequence();
    ~APSCCMoveSequence();
    
    static APSCCMoveSequence *actionOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo, bool finishRecovery=false);
    
    bool initOneTwo(cocos2d::CCFiniteTimeAction *pActionOne, cocos2d::CCFiniteTimeAction *pActionTwo, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() { return m_finishRecovery; }
    
protected:
    cocos2d::CCPoint m_startPosition;
    bool m_finishRecovery;
};
/** @brief APSCCRotateTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance. 
 
 */
class APSCCRotateTo : public cocos2d::CCRotateTo {
public:
    APSCCRotateTo();
    virtual ~APSCCRotateTo();
    
    static APSCCRotateTo *actionWithDuration(float duration, float angle, bool finishRecovery=false);
        
	/** initializes the action */
	bool initWithDuration(float duration, float angle, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

	virtual void startWithTarget(cocos2d::CCNode *node=NULL);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() const { return m_finishRecovery; }

protected:
    APSCCRotateTo *m_reverseAction;
    bool m_finishRecovery;
};

/** @brief APSCCRotateBy allows finishRecovery property
 */
class APSCCRotateBy : public cocos2d::CCRotateBy {
public:
    APSCCRotateBy();
    virtual ~APSCCRotateBy();
    
    static APSCCRotateBy *actionWithDuration(float duration, float angle, bool finishRecovery=false);

	/** initializes the action */
	bool initWithDuration(float duration, float angle, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
    virtual cocos2d::CCActionInterval *reverse();
    
    virtual void stop();
    
    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    bool m_finishRecovery;
};
/** @brief APSCCScaleTo 
 Cocos2D does not support reverse() method for none relative actions.
 However, ArtPig supports it by storing graphic states when a none relative
 action starts. In ArtPig, none relative action can have only one reverse 
 instance, so calling reverse() method multiple times returns only one instance. 
 
 */
class APSCCScaleTo : public cocos2d::CCScaleTo {
public:
    APSCCScaleTo();
    virtual ~APSCCScaleTo();
    
    static APSCCScaleTo *actionWithDuration(float duration, float sx, float sy, bool finishRecovery=false);

	/** initializes the action with and X factor and a Y factor */
	bool initWithDuration(float duration, float sx, float sy, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

	virtual void startWithTarget(cocos2d::CCNode *node=NULL);
    
    virtual void stop();
    
    virtual cocos2d::CCActionInterval *reverse();
    
    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    APSCCScaleTo *m_reverseAction;
    bool m_finishRecovery;
};

/** @brief APSCCScaleBy allows finishRecovery property
 */
class APSCCScaleBy : public cocos2d::CCScaleBy {
public:
    APSCCScaleBy();
    virtual ~APSCCScaleBy();
    
    static APSCCScaleBy *actionWithDuration(float duration, float sx, float sy, bool finishRecovery=false);
    
	/** initializes the action with and X factor and a Y factor */
	bool initWithDuration(float duration, float sx, float sy, bool finishRecovery=false);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
    virtual void stop();
    
    virtual cocos2d::CCActionInterval *reverse();
    
    bool getFinishRecovery() const { return m_finishRecovery; }
    
protected:
    bool m_finishRecovery;
};
/** @brief APSCCAnimateChildren 
 */
class APSCCAnimateChildren : public cocos2d::CCActionInterval {
    APS_SYNTHESIZE(artpig::APSGraphicGroup *, m_targetGraphic, TargetGraphic)
    APS_SYNTHESIZE_READONLY(float, m_interval, Interval)
    APS_SYNTHESIZE_READONLY(bool, m_wholeRange, WholeRange)
    APS_SYNTHESIZE_READONLY(bool, m_reversed, Reversed)
    APS_SYNTHESIZE_READONLY(unsigned int, m_originFrameIndex, OriginFrameIndex)
    APS_SYNTHESIZE_READONLY(unsigned int, m_frameCount, FrameCount)
    
public:
    APSCCAnimateChildren();
    virtual ~APSCCAnimateChildren();
    
    static APSCCAnimateChildren *actionWithDuration(float duration, unsigned int frameCount, artpig::APSGraphicGroup *targetGraphic);
    static APSCCAnimateChildren *actionWithDuration(float duration, unsigned int frameCount, artpig::APSGraphicGroup *targetGraphic, float interval);
    
    bool initWithDuration(float duration, unsigned int frameCount, artpig::APSGraphicGroup *targetGraphic);
    bool initWithDuration(float duration, unsigned int frameCount, artpig::APSGraphicGroup *targetGraphic, float interval);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
    virtual cocos2d::CCActionInterval *reverse(void);

    virtual void update(float time);
};

/** @brief APSCCAnimate 
 APSCCAnimate animates sprite with fixed interval for a duration. When the animation
 reaches the last sprite frame, the first sprite frame is used for the next 
 iteration.
 */
class APSCCAnimate : public cocos2d::CCAnimate {
    APS_SYNTHESIZE_READONLY(float, m_interval, Interval)
    APS_SYNTHESIZE_READONLY(unsigned int, m_originFrameIndex, OriginFrameIndex)
public:
    APSCCAnimate();
    virtual ~APSCCAnimate();
    
    static APSCCAnimate *actionWithDuration(float duration, cocos2d::CCAnimation *animation, bool restoreOriginalFrame);
    static APSCCAnimate *actionWithDuration(float duration, cocos2d::CCAnimation *animation, bool restoreOriginalFrame, float interval);
    
    bool initWithDuration(float duration, cocos2d::CCAnimation *animation, bool restoreOriginalFrame);
    bool initWithDuration(float duration, cocos2d::CCAnimation *animation, bool restoreOriginalFrame, float interval);
    
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);

    virtual cocos2d::CCActionInterval *reverse(void);
};

APS_END_NAMESPACE

#endif
