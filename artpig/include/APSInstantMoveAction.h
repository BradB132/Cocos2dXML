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

#ifndef ArtPigIOS_APSInstantMoveAction_h
#define ArtPigIOS_APSInstantMoveAction_h

#include "APSInstantGraphicAction.h"

APS_BEGIN_NAMESPACE(artpig)

class APSInstantMoveAction : public APSInstantGraphicAction {
    APS_CLASS_NAME(APSInstantMoveAction)
    
    /** endPosition is the end position of target graphic after action is applied.
     If action is relative, endRotation indicates relative state for target graphic.
     */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_endPosition, EndPosition)
    
public:
    /** Constructor of APSInstantMoveAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSInstantMoveAction(APSDictionary *properties=NULL);   
    
	virtual ~APSInstantMoveAction();
    
    /** Initializes APSInstantMoveAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns a type of this action.                     */
    virtual APSActionType getActionType() const { return kAPSActionTypeMove; };
    
    /** Applies instant fade to target graphic. 
     @warning Although instantMove() is declared in public, it should be called solely by cocos2d::CCAction's execution of this action.
     */
    void instantMove(cocos2d::CCNode* pSender);  
    
protected:
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    virtual cocos2d::CCFiniteTimeAction * makeMidCCAction(bool universal=false, float scale=1.0f);     
    };

APS_END_NAMESPACE

#endif
