//
//  APSSpriteSheetHolder.h
//  ArtPigEditor
//
//  Created by Kim Kiyoung on 5/7/12.
//  Copyright (c) 2012 ArtPigSoft. All rights reserved.
//

#ifndef ArtPigEditor_APSSpriteSheetHolder_h
#define ArtPigEditor_APSSpriteSheetHolder_h

#include "APSSpriteFrame.h"
#include "APSImageHolder.h"

APS_BEGIN_NAMESPACE(artpig)


class APSSpriteSheetHolder : public APSImageHolder {
    APS_CLASS_NAME(APSSpriteSheetHolder)
    
    APS_PROPERTY_KEY(Frames)
    
    APS_SYNTHESIZE(bool, m_isCached, IsCached)
    
public:
    static void getPlFilenameWithImageFilename(std::string *plFilename, const char *imageFile);
    
    static const char *getPlFileExtension() { return "plist"; }
    

    APSSpriteSheetHolder(const char *code="", APSResourceManager *manager=NULL);
    
    APSSpriteSheetHolder(APSDictionary *properties);
    
	virtual ~APSSpriteSheetHolder();
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** preloads image before it is used.                            */
    virtual void preloadData();
    
    /** Minimizes memory usage.                                 */
    virtual void clearCachedData();
    
    cocos2d::CCSpriteFrame *getCCSpriteFrameAtIndex(unsigned int index);
    
//    virtual const char *getSheetInternalName();
    
    const char *getRuntimePlPath();
    
    /** if loadCache==true, sprite frames are cached from file.
     */
    std::vector<APSSpriteFrame *> *getFrames(bool loadCache=true);
    
    unsigned int getCount() { return m_frames.size(); }
    
protected:
    std::vector<APSSpriteFrame *> m_frames;
    std::map<const std::string, APSSpriteFrame *> m_framesMap;
    std::string *m_runtimePlPath;
};

APS_END_NAMESPACE


#endif
