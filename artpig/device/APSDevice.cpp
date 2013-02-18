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

#include "APSDevice.h"
#include <sstream>

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSDevice::getIdentifierKey() {
    static const string key = "identifier";
    return key;
}

const string &APSDevice::getEnabledKey() {
    static const string key = "enabled";
    return key;
}

const string &APSDevice::getScreenSizeKey() {
    static const string key = "screenSize";
    return key;
}

APSDevice::APSDevice(const char *identifier, CCSize screenSize) :
m_screenSize(screenSize),
m_enabled(false),
m_identifier("")
{
    this->setIdentifier(identifier);
}

APSDevice::APSDevice(const APSDevice &device) :
m_screenSize(device.getScreenSize()),
m_enabled(device.getEnabled())
{
    this->setIdentifier(device.getIdentifier());
}

APSDevice::APSDevice(APSDictionary *properties) :
m_screenSize(CCSizeZero),
m_enabled(false)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSDevice::~APSDevice() {
}

bool APSDevice::initWithProperties(APSDictionary *properties) {
    // set identifier
    APSString *str = (APSString *)properties->getObjectForKey(this->getIdentifierKey());
    if (str) {
        this->setIdentifier(str->c_str());
    }
    

    // set enabled
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getEnabledKey());
    if (number) {
        this->setEnabled(number->getBoolean());
    }
    
    // set screenSize
    str = (APSString *)properties->getObjectForKey(this->getScreenSizeKey());
    if (str) {
        this->setScreenSize(str->getSizeValue());
    }
    
    /*
    number = (APSNumber *)properties->getObjectForKey(kAPSDevice_screenWidthKey);
    if (number) {
        this->m_screenSize.width = number->getFloat();
    }
    
    number = (APSNumber *)properties->getObjectForKey(kAPSDevice_screenHeightKey);
    if (number) {
        this->m_screenSize.height = number->getFloat();
    }
        */
    return true;
}

APS_END_NAMESPACE
