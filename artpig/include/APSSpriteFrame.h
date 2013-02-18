//
//  APSSpriteFrame.h
//  ArtPigEditor
//
//  Created by Kim Kiyoung on 5/7/12.
//  Copyright (c) 2012 ArtPigSoft. All rights reserved.
//

#ifndef ArtPigEditor_APSSpriteFrame_h
#define ArtPigEditor_APSSpriteFrame_h

#include "APSElements.h"


APS_BEGIN_NAMESPACE(artpig)

class APSSpriteSheetHolder;

class APSSpriteFrame {
    APS_SYNTHESIZE_WITH_KEY(unsigned int, m_frameIndex, FrameIndex)
    
    APS_SYNTHESIZE_STRING_WITH_KEY(m_name, Name)
    
    APS_SYNTHESIZE_STRING_WITH_KEY(m_internalName, InternalName)
    
    APS_SYNTHESIZE(APSSpriteSheetHolder *, m_spriteSheetHolder, SpriteSheetHolder)
    
public:
    APSSpriteFrame();
    
    APSSpriteFrame(APSDictionary *properties, APSSpriteSheetHolder *sprietSheetHolder);
    
    virtual ~APSSpriteFrame();
        
    cocos2d::CCSpriteFrame *getCCSpriteFrame() const { return m_ccSpriteFrame; }
    void setCCSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame) { m_ccSpriteFrame = spriteFrame; }
    
protected:
    cocos2d::CCSpriteFrame *m_ccSpriteFrame;
};

APS_END_NAMESPACE

#endif
