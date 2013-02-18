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

/*
    - Position of the first anchor is used for start position, and it is assigned from graphic's position at the point that the graphic is begin moves.
*/
#ifndef ArtPigIOS_APSBezierMoveAction_h
#define ArtPigIOS_APSBezierMoveAction_h

#include "APSIntervalGraphicAction.h"
#include "APSAnchor.h"

APS_BEGIN_NAMESPACE(artpig)

class APSBezierMoveAction : public APSIntervalGraphicAction {
    APS_CLASS_NAME(APSBezierMoveAction)

    APS_PROPERTY_KEY(Anchors)

public:
    /** Constructor of APSBezierMoveAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSBezierMoveAction(APSDictionary *properties=NULL);    
	virtual ~APSBezierMoveAction();
    
    /** Initializes APSBezierMoveAction object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    std::vector<APSAnchor *> *getAnchors();
    
protected:
    virtual void saveNodeState();
    
    virtual void restoreNodeState();
    
    /** Creates and returns an autoreleased cocos2d graphic action object.
     */
    virtual cocos2d::CCActionInterval * makeGraphicCCAction(bool universal=false, float scale=1.0f);

    std::vector<APSAnchor *> m_anchors;
};

APS_END_NAMESPACE

#endif
