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

#ifndef ArtPigIOS_APSPlatform_h
#define ArtPigIOS_APSPlatform_h


#include "APSSharedType.h"
#include <string>

APS_BEGIN_NAMESPACE(artpig)

class APSPlatform {
public:
    
    APSPlatform();
       
    /** Returns a shared instance of the APSPlatform object.            */
    static APSPlatform *sharedPlatform();

    /** Returns the full pathname of the directory containing resources.    */
    static const char *getResourcePathForFile(const char *name);
    
    cocos2d::CCPoint convertPointFromPixels(const cocos2d::CCPoint &point);    
    cocos2d::CCPoint convertPointToPixels(const cocos2d::CCPoint &point);
    
    cocos2d::CCSize convertSizeFromPixels(const cocos2d::CCSize &size);
    cocos2d::CCSize convertSizeToPixels(const cocos2d::CCSize &size);
    
    APS_SYNTHESIZE(cocos2d::CCSize, m_winSizeInPixels, WinSizeInPixels)
    APS_SYNTHESIZE(float, m_scaleFactor, ScaleFactor)
    
};

APS_END_NAMESPACE

#endif
