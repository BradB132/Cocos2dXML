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

#ifndef ArtPigEditor_APSAnchor_h
#define ArtPigEditor_APSAnchor_h

#include "APSElements.h"

APS_BEGIN_NAMESPACE(artpig)

class APSAnchor {
    APS_CLASS_NAME(APSAnchor)
    
    /** Position of anchor.                             */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_position, Position)
    
    /** Position of back handle.                        */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_backHandle, BackHandle)   
    
    /** Position of front handle.                        */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_frontHandle, FrontHandle)
    
    /** Length proportion from anchor's position to front handle assuming that
     whole length of bezier path is 1.
     */
    APS_SYNTHESIZE_WITH_KEY(float, m_proportion, Proportion)
    
public:
    APSAnchor(cocos2d::CCPoint position=cocos2d::CCPointZero, cocos2d::CCPoint backHandle=cocos2d::CCPointZero, cocos2d::CCPoint frontHandle=cocos2d::CCPointZero, float proportion=1.f);
    APSAnchor(APSDictionary *properties);
    APSAnchor(const APSAnchor &anchor);
    
    virtual ~APSAnchor();
    
    /** Initializes APSAnchor object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
    
    // Returns position of the anchor, scaled by a given scale value.
    cocos2d::CCPoint getPosition(float scale);
    
    // Returns back handle point of the anchor, scaled by a given scale value.
    cocos2d::CCPoint getBackHandle(float scale);
    
    // Returns front handle point of the anchor, scaled by a given scale value.
    cocos2d::CCPoint getFrontHandle(float scale);
};

APS_END_NAMESPACE

#endif
