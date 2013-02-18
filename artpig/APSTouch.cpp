//
//  APSEvent.cpp
//  ArtPigIOS
//
//  Created by Kim Kiyoung on 5/31/12.
//  Copyright (c) 2012 ARTPIGSOFT. All rights reserved.
//

#include "APSTouch.h"

APS_BEGIN_NAMESPACE(artpig)

APSTouch::APSTouch(APSEventType type, cocos2d::CCPoint position, int tapCount) :
m_type(type),
m_position(position),
m_tapCount(tapCount)
{
}

APSTouch::~APSTouch() {
}

APS_END_NAMESPACE
