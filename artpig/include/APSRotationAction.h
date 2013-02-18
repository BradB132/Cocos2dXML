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


#ifndef ArtPigIOS_APSRotationAction_h
#define ArtPigIOS_APSRotationAction_h

#include "APSIntervalGraphicAction.h"


APS_BEGIN_NAMESPACE(artpig)

class APSRotationAction : public APSIntervalGraphicAction {
    APS_CLASS_NAME(APSRotationAction)
    
    /** Saved rotation of target graphic before rotate action is applied. 
     */
    APS_SYNTHESIZE(float, m_startRotation, StartRotation)
    
    /** endRotation is the end rotation of target graphic after action is applied.
     If action is relative, endRotation represents relative rotation from target graphic.
     */
    APS_SYNTHESIZE_WITH_KEY(float, m_endRotation, EndRotation)
    
public:
    /** Constructor of APSRotationAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSRotationAction(APSDictionary *properties=NULL);    
	virtual ~APSRotationAction();
    
    /** Initializes APSRotationAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns a type of this action.                     */
    virtual APSActionType getActionType() const { return kAPSActionTypeRotation; }

protected:
    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f);
    
    // graphic의 상태값을 저장한다.
    virtual void saveNodeState();
    
    // graphic의 상태값을 복구한다.
    virtual void restoreNodeState();

};

APS_END_NAMESPACE

#endif
