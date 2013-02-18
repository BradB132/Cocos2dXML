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

#include "APSResourceManager.h"
#include "APSMedium.h"
#include "APSSymbol.h"
#include "APSXMLParser.h"
#include "APSSpriteSheetHolder.h"
#include <iostream>

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


typedef map<const string, APSResourceManager *> APSResourceManagerMap;

static APSResourceManagerMap resourceManagersCache;

const string &APSResourceManager::getVersionKey() {
    static const string key = "version";
    return key;
}

const string &APSResourceManager::getProjectIdKey() {
    static const string key = "projectId";
    return key;
}

const string &APSResourceManager::getDeviceInfoKey() {
    static const string key = "deviceInfo";
    return key;
}

const string &APSResourceManager::getMediumsKey() {
    static const string key = "mediums";
    return key;
}

APSResourceManager::APSResourceManager(const char *projectId, const char *location) :
m_deviceInfo(NULL),
m_symbolProperties(NULL)
{
    
    this->setProjectId(projectId);
    
    if (location) {
        this->setLocation(location);
    }
    
    m_symbolProperties = new APSDictionary();
    
}

APSResourceManager::~APSResourceManager() {
    
    APS_FOREACH(APSMediumMap, this->m_mediums, iter) {
        APS_SAFE_DELETE(iter->second);
    }
        APS_SAFE_DELETE(m_deviceInfo)
    
    APS_SAFE_RELEASE(m_symbolProperties);
}


APSResourceManager *APSResourceManager::getResourceManagerForProjectId(const char *projectId, const char *location) {
    APSResourceManager *resourceManager = resourceManagersCache[projectId];
    
    if (!resourceManager) {
                
        resourceManager = new APSResourceManager(projectId, location);
        APSXMLParser *parser = new APSXMLParser();
        
        string filename = APSResourceManager::getXMLFilenameForProjectId(projectId);
        std::string path = resourceManager->getPathForFilename(filename.c_str());
        
        if(parser->loadFile(path.c_str()) && resourceManager->initWithProperties(parser->getDictionary())) {
            resourceManagersCache[projectId] = resourceManager;
            
            // Find and set current device in runtime.
            APSDeviceInfo *devInfo = resourceManager->getDeviceInfo();
            devInfo->setAppliedDevice(devInfo->getMostFittingDevice());
        } else {
            APS_SAFE_DELETE(resourceManager)
            APSLOG("Failed to load project '%s'.", projectId);
        }
        APS_SAFE_DELETE(parser)
    }
    return resourceManager;
}

void APSResourceManager::removeResourceManagerForProjectId(const string &projectId) {
    APSResourceManager *rm = resourceManagersCache[projectId];
    if (rm) {
        resourceManagersCache.erase(projectId);
        delete rm;
    }
}

void APSResourceManager::removeAllResourceManagers() {
    for(map<const string, APSResourceManager *>::const_iterator itr = resourceManagersCache.begin(); itr != resourceManagersCache.end(); ++itr) {
        if(itr->second) {
            delete itr->second;
        }
    }
    resourceManagersCache.clear();
}

string APSResourceManager::getXMLFilenameForProjectId(const string &projectId) {
    return projectId+"_RM.xml";
}

APSResource *APSResourceManager::newResourceWithProperties(APSDictionary *properties, APSSymbol *parentSymbol) {
    // retrieve class name
    APSString *cn = (APSString *)properties->getObjectForKey(APSObject::getClassNameKey());
    if (cn) {
        // Allocate a resource object with the class name 
        APSResource *rs = (APSResource *)APSResourceManager::allocForClassName(cn->getString());
        if (rs) {
            rs->setParentSymbol(parentSymbol);
            
            // Initialize with the properties in the dictionary, and add into the resource list.
            rs->initWithProperties(properties);
        } else {
            APSLOG("Creating a resource failed for class %s.", cn->getString().c_str());
            return NULL;
        }
        return rs;
    }
    
    return NULL;
}

APSMedium *APSResourceManager::getMediumForCode(const string &code) {
    return m_mediums[code];
}

CCPoint APSResourceManager::getScaleModelToDevice(APSOrientation orientation, bool keepRatio) const {
    CCSize screenSize = APSPlatform::sharedPlatform()->getWinSizeInPixels();
    if (orientation==kAPSOrientationPortrait || orientation==kAPSOrientationPortraitUpsideDown) {
        screenSize = CCSize(screenSize.height, screenSize.width);
    }
    
    CCSize modelSize = this->getDeviceInfo()->getMainModelDevice()->getScreenSize();
    if (keepRatio) {
        CCPoint rate = CCPoint(screenSize.width/modelSize.width, screenSize.height/modelSize.height);
        
        // Choose the minimum scale change from model device size
        float scale = fminf(rate.x, rate.y);
        return CCPoint(scale, scale);
    } else {
        return CCPoint(screenSize.width/modelSize.width, screenSize.height/modelSize.height);
    }
}

bool APSResourceManager::initWithProperties(APSDictionary *properties) {

    APSString *version = (APSString *)properties->getObjectForKey(this->getVersionKey());
    if (version) {
        this->setVersion(atof(version->c_str()));
    }

    // set projectId
    APSString *projectId = (APSString *)properties->getObjectForKey(this->getProjectIdKey());
    if (projectId) {
        this->setProjectId(projectId->c_str());
    }
    
    // set deviceInfo. This part comes first so that newly created resources can use deviceInfo. 
    APSDictionary *dict = (APSDictionary *)properties->getObjectForKey(this->getDeviceInfoKey());
    if (dict) {
        this->m_deviceInfo = new APSDeviceInfo;
        if(!this->m_deviceInfo->initWithProperties(dict)) {
            return false;
        }
    }
    
    // set m_mediums
    APSArray *array = (APSArray *)properties->getObjectForKey(this->getMediumsKey());
    if (array) {
        APS_FOREACH(APSArrayStorage, *array, iter) {
            APSDictionary *dict = (APSDictionary *)*iter;
            // retrieve class name
            APSString *cn = (APSString *)dict->getObjectForKey(APSObject::getClassNameKey());
            if (cn) {
                // Allocate a resource object with the class name 
                APSMedium *medium = (APSMedium *)allocForClassName(cn->c_str());
                if (medium) {                    
                    // initialize with the properties in the dictionary, and add into the resource list.
                    if(!medium->initWithProperties(dict)) {
                        return false;
                    }
                    
                    this->addMedium(medium);
                } else {
                    APSLOG("Failed to create class %s.", cn->getString().c_str());
                    return false;
                }
            }
        }
    }

    return true;
}

APSSymbol *APSResourceManager::newSymbol(const char *tag, bool applyScale, bool cacheProperties) {
    // Check if symbol properties are cached.
    APSDictionary *symProp = (APSDictionary *)m_symbolProperties->getObjectForKey(tag);
    
    if (!symProp) {
        string filename = APSSymbol::getXMLFilename(this->getProjectId(), tag);

        string path = this->getPathForFilename(filename.c_str());
        
        APSLOG("Loading APSSymbol with tag '%s'.",tag);

        APSXMLParser *parser = new APSXMLParser();
        if(parser->loadFile(path.c_str())) {
            symProp = parser->getDictionary();
            // Cache properties for later use.
            if (cacheProperties) {
                m_symbolProperties->setObjectForKey(parser->getDictionary(), tag);
            }
        }
        APS_SAFE_DELETE(parser)
    }
    
    if (symProp) {
        APSSymbol *symbol = new APSSymbol(symProp);
        /*
        // Backward compatibility. Symbol in old file does not have isRoot property.
        if (this->getVersion()+0.00001 < APS_APP_FILE_VERSION) {
            symbol->setIsRoot(true);
        }
        */
        
        if (symbol->getIsRoot()) {
            if (applyScale) {
                // In case of single symbol mode(=symbol does not contain sub-symbol)
                symbol->setScale(this->getScaleModelToDevice(symbol->getOrientation()));
            }
            
            // Position in the center of screen.
            CCSize scrSize = CCDirector::sharedDirector()->getWinSize();
            symbol->setPosition(CCPointMake(scrSize.width*0.5, scrSize.height*0.5));
            
            switch (symbol->getOrientation()) {
                case kAPSOrientationPortrait:
                    symbol->setRotation(90);
                    break;
                case kAPSOrientationPortraitUpsideDown:
                    symbol->setRotation(-90);
                    break;
                case kAPSOrientationLandscapeLeft:
                    symbol->setRotation(180);
                    break;
                default:
                    break;
            }
        }

        symbol->setResourceManager(this);
        return symbol;
    } else {
        APSLOG("Failed to load symbol with tag '%s'.", tag);
    }
    
    return NULL;
}

void APSResourceManager::addMedium(APSMedium *medium) {
    this->m_mediums[medium->getCode_string()] = medium;
    medium->setResourceManager(this);
}

string APSResourceManager::getPathForFilename(const char *filename) const {
    if (*this->getLocation()) {
        string str = this->getLocation();
        str.append("/");
        str.append(filename);
        return str;
    } else {
        return APSPlatform::getResourcePathForFile(filename);
    }
}

APS_END_NAMESPACE


#include "APSImageHolder.h"
#include "APSGraphicGroup.h"
#include "APSSprite.h"
#include "APSActionGroup.h"
#include "APSAudioAction.h"
#include "APSLinkerAction.h"
#include "APSGraphicAction.h"
#include "APSInstantFadeAction.h"
#include "APSInstantMoveAction.h"
#include "APSInstantRotationAction.h"
#include "APSInstantScaleAction.h"
#include "APSVisibilityAction.h"
#include "APSFadeAction.h"
#include "APSMoveAction.h"
#include "APSRotationAction.h"
#include "APSScaleAction.h"
#include "APSAnchor.h"
#include "APSBezierMoveAction.h"
#include "APSAnimateAction.h"
#include "APSAudioHolder.h"
#include "APSSpriteSheetHolder.h"
#include "APSSymbol.h"

APS_BEGIN_NAMESPACE(artpig)

APSResource *APSResourceManager::allocForClassName(const string &name) {
    static map<const string, APSResource *(*)()> *allocators=NULL;
    
    if (!allocators) {
        allocators = new map<const string, APSResource *(*)()>;
        
        (*allocators)[APSResource::className()] = (APSResource *(*)())(APSResource::alloc);
        
        //
        //  Graphic
        //
        (*allocators)[APSSymbol::className()] = (APSResource *(*)())APSSymbol::alloc;
        (*allocators)[APSGraphic::className()] = (APSResource *(*)())APSSprite::alloc;
        (*allocators)[APSGraphicGroup::className()] = (APSResource *(*)())APSGraphicGroup::alloc;
        (*allocators)[APSSprite::className()] = (APSResource *(*)())APSSprite::alloc;        //
        //  Action
        //
        (*allocators)[APSAction::className()] = (APSResource *(*)())APSAction::alloc;
        (*allocators)[APSActionGroup::className()] = (APSResource *(*)())APSActionGroup::alloc;
        (*allocators)[APSAudioAction::className()] = (APSResource *(*)())APSAudioAction::alloc;
        (*allocators)[APSLinkerAction::className()] = (APSResource *(*)())APSLinkerAction::alloc;        (*allocators)[APSInstantFadeAction::className()] = (APSResource *(*)())APSInstantFadeAction::alloc;
        (*allocators)[APSInstantMoveAction::className()] = (APSResource *(*)())APSInstantMoveAction::alloc;
        (*allocators)[APSInstantRotationAction::className()] = (APSResource *(*)())APSInstantRotationAction::alloc;
        (*allocators)[APSInstantScaleAction::className()] = (APSResource *(*)())APSInstantScaleAction::alloc;
        (*allocators)[APSVisibilityAction::className()] = (APSResource *(*)())APSVisibilityAction::alloc;
        (*allocators)[APSFadeAction::className()] = (APSResource *(*)())APSFadeAction::alloc;
        (*allocators)[APSMoveAction::className()] = (APSResource *(*)())APSMoveAction::alloc;
        (*allocators)[APSRotationAction::className()] = (APSResource *(*)())APSRotationAction::alloc;
        (*allocators)[APSScaleAction::className()] = (APSResource *(*)())APSScaleAction::alloc;
        (*allocators)[APSAnchor::className()] = (APSResource *(*)())APSAnchor::alloc;
        (*allocators)[APSBezierMoveAction::className()] = (APSResource *(*)())APSBezierMoveAction::alloc;
        (*allocators)[APSAnimateAction::className()] = (APSResource *(*)())APSAnimateAction::alloc;
        
        //
        //  Media
        //
        (*allocators)[APSAudioHolder::className()] = (APSResource *(*)())APSAudioHolder::alloc;
        (*allocators)[APSImageHolder::className()] = (APSResource *(*)())APSImageHolder::alloc;
        (*allocators)[APSSpriteSheetHolder::className()] = (APSResource *(*)())APSSpriteSheetHolder::alloc;
    }
    
    APSResource *(*alloc)() = (*allocators)[name];
    if (alloc) {
        return (APSResource *)alloc();
    }
     return NULL;
}

APS_END_NAMESPACE
