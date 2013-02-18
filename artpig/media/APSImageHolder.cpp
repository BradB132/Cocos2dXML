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

#include "APSImageHolder.h"
#include "APSSymbol.h"
#include "APSDeviceInfo.h"
#include "APSResourceManager.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const string &APSImageHolder::getModelTextureSizeKey() {
    static const string key = "modelTextureSize";
    return key;
}

APSImageHolder::APSImageHolder(const char *code, APSResourceManager *manager) :
APSMedium(code, manager),
m_runtimeFullPath(NULL),
m_runtimeFilename(NULL),
m_modelTextureSize(CCSizeZero)
{
}

APSImageHolder::APSImageHolder(APSDictionary *properties) :
m_runtimeFullPath(NULL),
m_runtimeFilename(NULL),
m_modelTextureSize(CCSizeZero)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSImageHolder::~APSImageHolder() {
    APS_SAFE_DELETE(m_runtimeFilename)
    
    APS_SAFE_DELETE(m_runtimeFullPath)
}

bool APSImageHolder::initWithProperties(APSDictionary *properties) {
    bool ok = APSMedium::initWithProperties(properties);
    
    if (ok) {
        APSString *string = (APSString *)properties->getObjectForKey(this->getModelTextureSizeKey());
        if (string) {
            this->setModelTextureSize(string->getSizeValue());
        }
    }
    
    return ok;
}

void APSImageHolder::preloadData() {
    APSMedium::preloadData();
    
    // Simply calling this method populates the texture data.
    this->getTexture();
}

string APSImageHolder::getFilenameForDevice(APSDevice *device) {
    if (*this->getFilename() && device) {
        APSPathFields fields;
        APSString::getPathFields(this->getFilename(), &fields);
        // fields.name+"_"+device->getIdentifier()+"."+fields.extension;
        fields.name.append("_");
        fields.name.append(device->getIdentifier());
        fields.name.append(".");
        fields.name.append(fields.extension);
        return fields.name;
    }
    return "";
}

const string &APSImageHolder::getRuntimeFilename() {
    if (!this->m_runtimeFilename) {
        // retrieve current device 
        APSDevice *device = this->getResourceManager()->getDeviceInfo()->getAppliedDevice();
        if (device) {
            this->m_runtimeFilename = new std::string(this->getFilenameForDevice(device));
        }
    }

    return *this->m_runtimeFilename;
}

CCTexture2D *APSImageHolder::getTexture() {
    CCTexture2D *texture=NULL;
    // create texture        
    texture = CCTextureCache::sharedTextureCache()->addImage(this->getRuntimeFullPath()->c_str());
    return texture;
}

const string *APSImageHolder::getRuntimeFullPath() {
    if (!m_runtimeFullPath) {
        m_runtimeFullPath = new string(this->getResourceManager()->getPathForFilename(this->getRuntimeFilename().c_str()));
    }
    return m_runtimeFullPath;
}
APS_END_NAMESPACE

