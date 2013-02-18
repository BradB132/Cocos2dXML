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

#ifndef ArtPigEditor_APSAnimateAction_h
#define ArtPigEditor_APSAnimateAction_h

#include "APSIntervalGraphicAction.h"

APS_BEGIN_NAMESPACE(artpig)

class APSAnimateAction : public APSIntervalGraphicAction {
    APS_CLASS_NAME(APSAnimateAction)
    
    /** Saved scale of target graphic before frame index action is applied. 
     */
    APS_SYNTHESIZE(unsigned int, m_startFrameIndex, StartFrameIndex)
    
    /** If YES, animation begins with 0 frame and runs until it reaches the end frame.
     */
    APS_SYNTHESIZE_WITH_KEY(bool, m_isWholeRange, IsWholeRange)
    
    APS_SYNTHESIZE_WITH_KEY(float, m_interval, Interval)    
    
public:
    /** Constructor of APSAnimateAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSAnimateAction(APSDictionary *properties=NULL);    
	virtual ~APSAnimateAction();
    
    /** Initializes APSAnimateAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns a type of this action.                     */
    virtual APSActionType getActionType() const { return kAPSActionTypeAnimate; };    
    
protected:
    
    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f);
    
    virtual void saveNodeState();
    
    virtual void restoreNodeState();
};

APS_END_NAMESPACE

#endif
