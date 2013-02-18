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

#ifndef ArtPigIOS_APSMoveAction_h
#define ArtPigIOS_APSMoveAction_h

#include "APSIntervalGraphicAction.h"

APS_BEGIN_NAMESPACE(artpig)

class APSMoveAction : public APSIntervalGraphicAction {
    APS_CLASS_NAME(APSMoveAction)
    
    /** Saved position of target graphic before move action is applied. 
     */
    APS_SYNTHESIZE(cocos2d::CCPoint, m_startPosition, StartPosition)
    
    /** endPosition is the end position of target graphic after action is applied.
     If action is relative, endPosition represents relative position from target graphic.
     */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_endPosition, EndPosition)

public:
    /** Constructor of APSMoveAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSMoveAction(APSDictionary *properties=NULL);
    
	virtual ~APSMoveAction();
    
    /** Initializes APSMoveAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
            
    /** Returns a type of this action.                                  */
    virtual APSActionType getActionType() const { return kAPSActionTypeMove; };

protected:

    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f);

    virtual void saveNodeState();
    
    virtual void restoreNodeState();
    
};

APS_END_NAMESPACE

#endif
