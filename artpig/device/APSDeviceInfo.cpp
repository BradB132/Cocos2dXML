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

#include "APSDeviceInfo.h"
#include "APSPlatform.h"
#include <cmath>
#include <cfloat>

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSDeviceInfo::getMainModelIndexKey() {
    static const string key = "mainModelIndex";
    return key;
}

const string &APSDeviceInfo::getDevicesKey() {
    static const string key = "devices";
    return key;
}

APSDeviceInfo::APSDeviceInfo(APSDictionary *properties) :
m_appliedDevice(NULL),
m_mainModelIndex(0),
m_devices(new vector<APSDevice *>)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSDeviceInfo::APSDeviceInfo(const APSDeviceInfo &deviceInfo) :
m_appliedDevice(NULL),
m_mainModelIndex(0),
m_devices(new vector<APSDevice *>)
{
    this->m_mainModelIndex = deviceInfo.getMainModelIndex();
    
    APS_FOREACH(vector<APSDevice *>, *deviceInfo.getDevices(), iter) {
        APSDevice *dev = new APSDevice(*(APSDevice*)*iter);
        this->m_devices->push_back(dev);
    }
}

APSDeviceInfo::~APSDeviceInfo() {
    APS_FOREACH(vector<APSDevice *>, *this->m_devices, iter) {
        APS_SAFE_DELETE(*iter);
    }
    APS_SAFE_DELETE(this->m_devices);
}

bool APSDeviceInfo::initWithProperties(APSDictionary *properties) {
    
    // set mainModelIndex
    APSNumber *number = (APSNumber *)properties->getObjectForKey(this->getMainModelIndexKey());
    if (number) {
        this->setMainModelIndex(number->getInteger());
    }
    
    // set devices
    APSArray *devices = (APSArray *)properties->getObjectForKey(this->getDevicesKey());
    if (devices) {
        APS_FOREACH(APSArrayStorage, *devices, iter) {
            APSDictionary *dict = (APSDictionary *)*iter;

            // Allocate a device object with the class name 
            APSDevice *dv = new APSDevice;
            
            // initialize with the properties in the dictionary.
            if(!dv->initWithProperties(dict))
                return false;
            this->m_devices->push_back(dv);

        }
        
        // main model device is the default for applied device.
        this->setAppliedDevice(this->getMainModelDevice());
    }
    
    return true;
}

APSDevice *APSDeviceInfo::getMainModelDevice() {
    return (*this->m_devices)[this->getMainModelIndex()];
}

APSDevice *APSDeviceInfo::getMostFittingDevice() {
//    const CCSize screenSize = APSPlatform::sharedPlatform()->getDeviceScreenSize();
//    float screenScale = APSPlatform::sharedPlatform()->getDeviceScale();
    CCSize winSizeInPixels = APSPlatform::sharedPlatform()->getWinSizeInPixels();
    
//    // If APSPlatform cannot find runtime screen size, main model device is used.
//    if (isZeroF(winSizeInPixels.width)) {
//        return this->getMainModelDevice();
//    }
    
    APSDevice *selectedDevice = NULL;
    double selectedDistance = FLT_MAX;
    
    APS_FOREACH(vector<APSDevice *>, *this->m_devices, iter) {
        APSDevice *dev = (APSDevice *)*iter;
        if (dev->getEnabled()) {
            CCSize size = dev->getScreenSize();
            double distance = pow(1-size.width/winSizeInPixels.width, 2) + pow(1-size.height/winSizeInPixels.height, 2);
            if (selectedDistance > distance) {
                selectedDevice = dev;
                selectedDistance = distance;
            }
        }
    }
    
    return selectedDevice;
}

float APSDeviceInfo::getScreenScaleForDevice(APSDevice *device) {
    CCSize deviceSize = device->getScreenSize();
    CCSize modelSize = this->getMainModelDevice()->getScreenSize();
    CCPoint rate = CCPoint(deviceSize.width/modelSize.width, deviceSize.height/modelSize.height);
    
    // Choose the minimum scale change from model device size
    return fabs(1-rate.x) < fabs(1-rate.y) ? rate.x : rate.y;
    
}

APS_END_NAMESPACE
