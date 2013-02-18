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

#ifndef ArtPigIOS_APSGraphicAction_h
#define ArtPigIOS_APSGraphicAction_h

#include "APSAction.h"


APS_BEGIN_NAMESPACE(artpig)

/**
 @brief	APSGraphicAction defines general properties and methods of graphic related actions.
*/
class APSGraphicAction : public APSAction {
    APS_CLASS_NAME(APSGraphicAction)
        
    /** true if the end state of target graphic is relative to beginning state of it.  */
    APS_SYNTHESIZE_WITH_KEY(bool, m_relative, Relative)
    
public:
    /** Constructor of APSGraphicAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSGraphicAction(APSDictionary *properties=NULL);   
    
	virtual ~APSGraphicAction();
    
    /** Returns true if action is a kind of graphic actions.                */
    static bool isGraphicAction(APSAction *action);
    
    /** Initializes APSGraphicAction object with given properties.        */
    virtual bool initWithProperties(APSDictionary *properties);
        /** Returns an autoreleased cocos2d::CCAction object that can be applied to none ArtPig projects.  
     */
    virtual cocos2d::CCFiniteTimeAction *universalCCAction(float scale=1.0f);
    
    /** Saves current state of target graphic.  */
    virtual void saveNodeState(){};
    
    /** Restores saved value to target graphic.  */
    virtual void restoreNodeState(){};

    protected:    
};

APS_END_NAMESPACE

#endif
