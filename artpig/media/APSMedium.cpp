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

#include "APSMedium.h"
#include "APSResourceManager.h"
#include <iostream>

using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSMedium::getCodeKey() {
    static const string key = "code";
    return key;
}

const string &APSMedium::getFilenameKey() {
    static const string key = "filename";
    return key;
}

APSMedium::APSMedium(const char *code, APSResourceManager *manager) :
m_code(code),
m_resourceManager(manager)
{
}

APSMedium::APSMedium(APSDictionary *properties) :
m_resourceManager(NULL)
{
    if (properties) {
        this->initWithProperties(properties);
    }
}

bool APSMedium::initWithProperties(APSDictionary *properties) {
    
    // Set code
    APSString *string = (APSString *)properties->getObjectForKey(this->getCodeKey());
    if (string) {
        this->setCode(string->c_str());
    }

    // Set filename
    string = (APSString *)properties->getObjectForKey(this->getFilenameKey());
    if (string) {
        this->setFilename(string->c_str());
    }
    
    return true;
}

void APSMedium::setResourceManager(APSResourceManager *manager) {
    m_resourceManager = manager;
}

APSResourceManager *APSMedium::getResourceManager() const {
    return m_resourceManager;
}

APS_END_NAMESPACE
