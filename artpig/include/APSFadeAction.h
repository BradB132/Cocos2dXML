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

#ifndef ArtPigIOS_APSFadeAction_h
#define ArtPigIOS_APSFadeAction_h

#include "APSIntervalGraphicAction.h"

APS_BEGIN_NAMESPACE(artpig)

class APSFadeTo;

/**
 @brief	APSFadeAction defines fade action with some duration.
 APSFadeAction cannot be relative.
 */
class APSFadeAction : public APSIntervalGraphicAction {
    APS_CLASS_NAME(APSFadeAction)
    
    /** Saved opacity of target graphic before fade is applied. 
     */
    APS_SYNTHESIZE(unsigned int, m_startOpacity, StartOpacity)
    
    /** endOpacity is the end opacity of target graphic after action is applied.   
     */
    APS_SYNTHESIZE_WITH_KEY(unsigned int, m_endOpacity, EndOpacity)
    
public:
    /** Constructor of APSFadeAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSFadeAction(APSDictionary *properties=NULL);

	virtual ~APSFadeAction();
    
    /** Initializes APSFadeAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns a type of this action.                     */
    virtual APSActionType getActionType() const { return kAPSActionTypeFade; };
    
protected:
    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f);
    
    virtual void saveNodeState();
    
    virtual void restoreNodeState();

};

APS_END_NAMESPACE

#endif
