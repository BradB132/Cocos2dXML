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

#ifndef ArtPigIOS_APSDevice_h
#define ArtPigIOS_APSDevice_h

#include "APSResource.h"

APS_BEGIN_NAMESPACE(artpig)

class APSDevice {
    APS_CLASS_NAME(APSDevice)
    
    /** Identifier is used to distinguish device. Also identifier is used
     in setting image file names.
     */
    APS_SYNTHESIZE_STRING_WITH_KEY(m_identifier, Identifier)

    /** Screen size of device in pixel. In artpig, all points and sizes are
     assumed to be pixel based. 
     */
    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCSize, m_screenSize, ScreenSize)
    
    /** If true, images are generated for this device.
     */
    APS_SYNTHESIZE_WITH_KEY(bool, m_enabled, Enabled)

public:
    APSDevice(const char *identifier="", cocos2d::CCSize screenSize=cocos2d::CCSizeZero);
    APSDevice(const APSDevice &device);
    APSDevice(APSDictionary *properties);
    virtual ~APSDevice();

    virtual bool initWithProperties(APSDictionary *properties);
    };

APS_END_NAMESPACE
#endif


