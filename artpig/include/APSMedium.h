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

#ifndef ArtPigEditor_APSMedium_h
#define ArtPigEditor_APSMedium_h

#include "APSElements.h"
#include "APSResource.h"


APS_BEGIN_NAMESPACE(artpig)

class APSSymbol;
class APSDevice;
class APSAction;
class APSResourceManager;

class APSMedium : public APSResource {
    APS_CLASS_NAME(APSMedium)
    
    APS_SYNTHESIZE_STRING_WITH_KEY(m_code, Code)
    APS_SYNTHESIZE_STRING_WITH_KEY(m_filename, Filename)
    
public:
    APSMedium(const char *code="", APSResourceManager *manager=NULL);
    APSMedium(APSDictionary *properties);
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    virtual void preloadData() {};             // preloads data before it is used.
    virtual void clearCachedData() {};           // Minimizes memory usage.

    // Returns filename for device.
    //virtual const string getFilenameForDevice(APSDevice *device) const;
    
    void setResourceManager(APSResourceManager *manager);
    APSResourceManager *getResourceManager() const;
    
protected:
    APSResourceManager *m_resourceManager;
};

APS_END_NAMESPACE

#endif
