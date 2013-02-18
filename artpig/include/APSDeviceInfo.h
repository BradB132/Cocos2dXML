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

#ifndef ArtPigIOS_APSDeviceInfo_h
#define ArtPigIOS_APSDeviceInfo_h

#include "APSDevice.h"

APS_BEGIN_NAMESPACE(artpig)

class APSDeviceInfo {
    APS_CLASS_NAME(APSDeviceInfo)
    
    /** Index of main model device in devices list.                         */
    APS_SYNTHESIZE_WITH_KEY(unsigned int, m_mainModelIndex, MainModelIndex)
    
    /** Applied device that is selected out of devices list in runtime.     */
    APS_SYNTHESIZE_WITH_KEY(APSDevice *, m_appliedDevice, AppliedDevice)
    
    /** List of candiate devices.                                       */
    APS_SYNTHESIZE_READONLY_WITH_KEY(std::vector<APSDevice *> *, m_devices, Devices)
public:
    
    APSDeviceInfo(APSDictionary *properties=NULL);
    
    APSDeviceInfo(const APSDeviceInfo &deviceInfo);
    
    virtual ~APSDeviceInfo();
    
    bool initWithProperties(APSDictionary *properties);
        
    /** Returns main model device in devices list. mainModelIndex property must
     be set before using this method.
     */
    APSDevice *getMainModelDevice();
    
    /** Finds and returns APSDevice that the most matches to the runtime 
     device.
     */
    APSDevice *getMostFittingDevice();
    
    /** Returns an appropriate scale from model to a given device.           */
    float getScreenScaleForDevice(APSDevice *device);
    
};
APS_END_NAMESPACE

#endif

