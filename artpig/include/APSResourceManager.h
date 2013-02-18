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

#ifndef ArtPigEditor_APSResourceManager_h
#define ArtPigEditor_APSResourceManager_h

#include "APSElements.h"
#include "APSDeviceInfo.h"
#include "APSSymbol.h"

APS_BEGIN_NAMESPACE(artpig)

class APSMedium;
class APSSPriteFrame;

typedef std::map<const std::string, APSMedium *> APSMediumMap;
typedef std::map<const std::string, APSSymbol *> APSSymbolMap;

/** @brief APSResourceManager
 APSResourceManager helps to create APSResource and APSMedium objects. 
 Each project can have one resource manager.
 APSSymbol objects can be created by resource manager, and properties 
 information used to initialize symbol is cached to reuse it when a symbol with 
 the same tag is created again.
 
 If you create a symbol without resource manager, the symbol does not have 
 access to images. Therefore, cocos2d::CCSprite objects in symbol cannot be created
 with image textures.
*/
class APSResourceManager {
    APS_CLASS_NAME(APSResourceManager)

    APS_SYNTHESIZE_WITH_KEY(float, m_version, Version)
    
    APS_SYNTHESIZE_STRING_WITH_KEY(m_projectId, ProjectId)
    
    /** A directory where symbol files are stored. If location property is not
     set, default resource path is used. In case of IOS, location should be set
     only when xml and images files are stored other than path returned by
     [[NSBundle mainBundle] resourceURL].
     */
    APS_SYNTHESIZE_STRING_WITH_KEY(m_location, Location) 

    APS_PROPERTY_KEY(DeviceInfo)
    APS_PROPERTY_KEY(Mediums)
    
    APS_SYNTHESIZE_READONLY(APSDeviceInfo *, m_deviceInfo, DeviceInfo)
public:
    APSResourceManager(const char *projectId="", const char *location=NULL);

    virtual ~APSResourceManager();
    
    /** Returns an APSResourceManager object with a given project id. If there
     is no resource manager created yet with the project id, APSResourceManager
     object is allocated and cached.
     If files are not located in default resource path, location parameter should
     be set.
     */
    static APSResourceManager *getResourceManagerForProjectId(const char *projectId, const char *location=NULL);
    
    /** Deallocates an APSResourceManager object with a given project id.   */
    static void removeResourceManagerForProjectId(const std::string &projectId);
    
    /** Deallocates all APSResourceManager objects.                         */
    static void removeAllResourceManagers();
    
    /** Returns resource manager's XML filename for a given project id.     */
    static std::string getXMLFilenameForProjectId(const std::string &projectId);
            
    /** Allocates and returns a new APSResource object initialized by given
     properties. 
     @warning To allocate class object, properties must include an APSString 
     object specifying class name.
     */
    static APSResource *newResourceWithProperties(APSDictionary *properties, APSSymbol *parentSymbol=NULL);
    
    /** Allocates and returns a new resource with a given class name.   */
    static APSResource *allocForClassName(const std::string &name);
    
    /** Returns an APSMedium object with a given code in resource manager. 
     If there is no APSMedium object with the code, NULL is returned.
     */
    APSMedium *getMediumForCode(const std::string &code);
    
    /** Returns a scale value(x and y) which can make model screen size to fit
     with the runtime device's screen size.
     */
    cocos2d::CCPoint getScaleModelToDevice(APSOrientation orientation=kAPSOrientationLandscapeRight, bool keepRatio=false) const;
    
    /** Initializes resource manager with given properties.             */
    virtual bool initWithProperties(APSDictionary *properties);
    
    /** Allocates and returns symbol with a given tag. If cacheProperties is 
     true, symbol properties are cached and reused later newSymbol() call.
     */
    APSSymbol *newSymbol(const char *tag=kAPSDefaultSymbolTag, bool applyScale=true, bool cacheProperties=true);
    
    
    /** Returns full path for a given file name.                       */
    std::string getPathForFilename(const char *filename) const;
    
    void addMedium(APSMedium *medium);
        
protected:
    APSMediumMap m_mediums;
    APSDictionary *m_symbolProperties;
    };

APS_END_NAMESPACE

#endif
