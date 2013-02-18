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

#include "APSPlatform.h"

using namespace cocos2d;

APS_BEGIN_NAMESPACE(artpig)

APSPlatform *APSPlatform::sharedPlatform() {
    static APSPlatform *platform = NULL;
    if (!platform) {
        platform = new APSPlatform;
    }
    return platform;
}

APSPlatform::APSPlatform()
{
    CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
    float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    this->setWinSizeInPixels(size);
    this->setScaleFactor(scale);
}

const char *APSPlatform::getResourcePathForFile(const char *name) {
#if COCOS2D_VERSION >= 0x00020000
    return CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(name);
#else
    return CCFileUtils::fullPathFromRelativePath(name);
#endif//APS_SKIP
    }

CCPoint APSPlatform::convertPointFromPixels(const CCPoint &point) {
    float scale = this->getScaleFactor();
    return CCPointMake(point.x/scale, point.y/scale);
}

CCPoint APSPlatform::convertPointToPixels(const CCPoint &point) {
    float scale = this->getScaleFactor();
    return CCPointMake(point.x*scale, point.y*scale);
}

CCSize APSPlatform::convertSizeFromPixels(const CCSize &size) {
    float scale = this->getScaleFactor();
    return CCSizeMake(size.width/scale, size.height/scale);
}

CCSize APSPlatform::convertSizeToPixels(const CCSize &size) {
    float scale = this->getScaleFactor();
    return CCSizeMake(size.width*scale, size.height*scale);
}

APS_END_NAMESPACE





