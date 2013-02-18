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

#ifndef ArtPigIOSX_APXAnimationObserver_h
#define ArtPigIOSX_APXAnimationObserver_h

#include "cocos2d.h"
#include "APSSharedType.h"

APS_BEGIN_NAMESPACE(artpig)

class APXAnimation;
    
class APXAnimationObserver {
public:
    virtual void willStartAnimation(APXAnimation *animation)=0;
    virtual void didFinishAnimation(APXAnimation *animation)=0;
};

APS_END_NAMESPACE

#endif
