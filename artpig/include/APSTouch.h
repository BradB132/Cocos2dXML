//
//  APSEvent.h
//  ArtPigIOS
//
//  Created by Kim Kiyoung on 5/31/12.
//  Copyright (c) 2012 ARTPIGSOFT. All rights reserved.
//

#ifndef ArtPigIOS_APSTouch_h
#define ArtPigIOS_APSTouch_h

#include "APSSharedType.h"

APS_BEGIN_NAMESPACE(artpig)

class APSTouch {
    APS_SYNTHESIZE(APSEventType, m_type, Type)
    APS_SYNTHESIZE(cocos2d::CCPoint, m_position, Position)
    APS_SYNTHESIZE(int, m_tapCount, TapCount)
    
    APSTouch(APSEventType type=kAPSEventTypeTouchBegan, cocos2d::CCPoint position=cocos2d::CCPointZero, int tapCount=1);
    
    virtual ~APSTouch();
};

APS_END_NAMESPACE

#endif
