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

#ifndef ArtPigIOS_APSImageHolder_h
#define ArtPigIOS_APSImageHolder_h

#include "APSMedium.h"

APS_BEGIN_NAMESPACE(artpig)

class APSResourceManager;
class APSDevice;

class APSImageHolder : public APSMedium {
    APS_CLASS_NAME(APSImageHolder)

    APS_SYNTHESIZE_WITH_KEY(cocos2d::CCSize, m_modelTextureSize, ModelTextureSize)
    
public:
    APSImageHolder(const char *code="", APSResourceManager *manager=NULL);
    
    APSImageHolder(APSDictionary *properties);
    
	virtual ~APSImageHolder();
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Returns image file name that determined by applied device in runtime.
     Runtime file name is created when getRuntimeFilename() is called for the
     first time, and it returns the same instance for later calls.
     */
    const std::string &getRuntimeFilename();

    /** Returns image file name for a given device. 
     */
    virtual std::string getFilenameForDevice(APSDevice *device);
    
    /** Returns image's full path that determined by applied device in runtime.
     */
    const std::string *getRuntimeFullPath();
    
    /** preloads image before it is used.                            */
    virtual void preloadData();

    virtual cocos2d::CCTexture2D *getTexture();
    
protected:

    std::string *m_runtimeFullPath;
    const std::string *m_runtimeFilename;

};

APS_END_NAMESPACE

#endif
