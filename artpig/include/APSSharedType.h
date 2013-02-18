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

#ifndef ArtPigIOS_APSharedType_h
#define ArtPigIOS_APSharedType_h

#include "cocos2d.h"
#include "APSMacroCPP.h"

#ifdef TEST_COCOS2D_X
using namespace cocos2d;
#endif

#include "APSCommon.h"

#include <iostream>


typedef unsigned int APSIndex;

#if COCOS2D_VERSION >= 0x00020000
namespace cocos2d {
typedef CCFloat CGFloat;
}
#else
namespace cocos2d {
typedef CGFloat CCFloat;
}
#endif//APS_SKIP

APS_BEGIN_NAMESPACE(artpig)

typedef cocos2d::CCAffineTransform CGAffineTransform;

#ifdef __MAC_OS_X_VERSION_MAX_ALLOWED
inline NSPoint NSPointFromCCPoint(cocos2d::CCPoint p) {
    return NSMakePoint(p.x, p.y);
}

inline NSSize NSSizeFromCCSize(cocos2d::CCSize size) {
    return NSMakeSize(size.width, size.height);
}

inline cocos2d::CCPoint CCPointFromNSPoint(NSPoint p) {
    return cocos2d::CCPoint(p.x, p.y);
}

inline cocos2d::CCSize APSSizeFromNGSize(NSSize size) {
    return cocos2d::CCSize(size.width, size.height);
}
#endif


enum {
	// The device is in landscape mode, with the device held upright and the home button on the right side.
	kAPSOrientationLandscapeRight,
	// The device is in landscape mode, with the device held upright and the home button on the left side.
	kAPSOrientationLandscapeLeft,
	// The device is in portrait mode, with the device held upright and the home button at the bottom. If you do not specify any orientations, this orientation is assumed by default.
	kAPSOrientationPortrait,
	// The device is in portrait mode but upside down, with the device held upright and the home button at the top.
	kAPSOrientationPortraitUpsideDown
};
typedef unsigned int APSOrientation;

enum _APSEventType {
	kAPSEventTypeTouchBegan,    // The type of event source that occurs when touch begins.
	kAPSEventTypeTouchEnded,      // The type of event source that occurs when touch ends.
	kAPSEventTypeTouchMoved,    // The type of event source that occurs when touch moves.
	kAPSEventTypeTouchCancelled,    // The type of event source that occurs when touch cancelled.
//    kAPSEventTypeTouchStationary,
	kAPSEventTypeShakeBegan,    // The type of event source that occurs when shake begins.
	kAPSEventTypeShakeEnded,		// The type of event source that occurs after shake ends.
	kAPSEventTypeGravityChange	// The type of event source that occurs when the gravity changes.
};
typedef unsigned int APSEventType;

enum _APSTouchOption {
    kAPSTouchOptionRetain=1,
    kAPSTouchOptionAcceptMoveEnter=1<<1,  // If set, graphic accepts touch events that has begun external position.
    kAPSTouchOptionAcceptsOnlyVisible=1<<2 // If set, graphic accepts touch events only when it is visible in the screen.
};
typedef unsigned int APSTouchOption;

// #define kAPSEventTypeTouchBegin kAPSEventTypeTouchBegan
// #define kAPSEventTypeTouchEnd   kAPSEventTypeTouchEnded

// #define APS_TOUCH_EVENT_TYPES_COUNT 4

enum _ResourceType {
	kAPSResourceTypeNone,
	kAPSResourceTypeGraphic,
	kAPSResourceTypeAction,
	kAPSResourceTypeMedia,
	kAPSResourceTypePage
};

enum {
    kAPSLinkerTypeTrigger,				// Type of linker that triggers an action.
    kAPSLinkerTypeInterrupt,			// Type of linker that interrupts an action.
    kAPSLinkerTypeInterruptAll,			// Type of linker that interrupts all actions.
    kAPSLinkerTypeEnable,				// Type of linker that enables an action.
    kAPSLinkerTypeDisable,				// Type of linker that disables an action.
    kAPSLinkerTypeNotifyEvent			// Type of linker that notifies an event. !!! Never use this type to link actions.
};
typedef unsigned int APSLinkerType;

enum _actionType {
	kAPSActionTypeNone,                 // Does nothing, an empty action
    kAPSActionTypeGroup,                // Contains a series of actions.
	kAPSActionTypeMove,                     
	kAPSActionTypeScale,
	kAPSActionTypeRotation,                 
	kAPSActionTypeFade,
	kAPSActionTypeAnimate,
	kAPSActionTypeVisibility,
	kAPSActionTypeLinker,               
	kAPSActionTypeAudio,
	kAPSActionTypeSkew,
};
typedef unsigned int APSActionType;

#define APS_GRAPHIC_ACTION_TYPES_COUNT    5

enum _APSTimingMode {
	kAPSTimingModeLinear,
	kAPSTimingModeEaseIn,
	kAPSTimingModeEaseOut,
	kAPSTimingModeEaseInEaseOut,
	kAPSTimingModeEaseExponentialIn,
	kAPSTimingModeEaseExponentialOut,
	kAPSTimingModeEaseExponentialInOut,
	kAPSTimingModeEaseSineIn,
	kAPSTimingModeEaseSineOut,
	kAPSTimingModeEaseSineInOut,
	kAPSTimingModeEaseElasticIn,
	kAPSTimingModeEaseElasticOut,
	kAPSTimingModeEaseElasticInOut,
	kAPSTimingModeEaseBounceIn,
	kAPSTimingModeEaseBounceOut,
	kAPSTimingModeEaseBounceInOut,
	kAPSTimingModeEaseBackIn,
	kAPSTimingModeEaseBackOut,
	kAPSTimingModeEaseBackInOut
};

enum APSPredefinedResourceIndex {
    kAPSSymbolIndex,
    kAPSResetSymbolActionIndex,
    kAPSTriggerProloguesActionIndex,
    kAPSInterruptAllActionIndex
};
#define APS_PREDEFINED_RESOURCE_INDEXES_LENGTH  4

/*
 APS_APP_FILE_VERSION 
 1.0 -  March 20, 2012
        ArtPigEditor v1.01
 1.01 - July 12, 2012 
        ArtPigEditor v1.5
*/
#define APS_APP_FILE_VERSION 1.01

#define APS_LIB_VERSION 1.5

#define APS_MAX_OPACITY 255
#define APS_MIN_OPACITY 0

#ifndef UINT32_MAX
#define UINT32_MAX  (0xffffffff)
#endif
#ifndef INT32_MAX
#define 	INT32_MAX   0x7fffffffL
#endif
#ifndef INT32_MIN
#define 	INT32_MIN   (-INT32_MAX - 1L)
#endif

#define APS_NIL_INDEX UINT32_MAX
#define APS_MAX_PRIORITY INT32_MAX
#define APS_MIN_PRIORITY INT32_MIN

#define APS_MIN_TIMING_FACTOR 2
#define APS_MAX_TIMING_FACTOR 6

inline float easeElasticPeriod(float factor) {
    return 0.3+(factor-APS_MIN_TIMING_FACTOR)*0.0375;
}

/* x is almost close to zero value or negligible. */
inline int isZeroF(float x) {
    return (x<FLT_EPSILON && -x<FLT_EPSILON);
}

inline int isZeroD(double x) {
    return (x<DBL_EPSILON && -x<DBL_EPSILON);
}

inline cocos2d::CCPoint accpRotate(cocos2d::CCPoint point, float theta) {
    /*
     x' = Cos(Theta) * x - Sin(Theta) * y
     y' = Sin(Theta) * x + Cos(Theta) * y
     */
    
    return cocos2d::CCPoint(point.x*cosf(theta)-point.y*sinf(theta), point.x*sinf(theta)+point.y*cosf(theta));
}

inline cocos2d::CCPoint accpAdd(cocos2d::CCPoint p1, cocos2d::CCPoint p2) {
    return cocos2d::CCPoint(p1.x+p2.x, p1.y+p2.y);
}

inline cocos2d::CCPoint accpSub(cocos2d::CCPoint p1, cocos2d::CCPoint p2) {
    return cocos2d::CCPoint(p1.x-p2.x, p1.y-p2.y);
}

inline cocos2d::CCPoint accpCompMult(cocos2d::CCPoint p1, cocos2d::CCPoint p2) {
    return cocos2d::CCPoint(p1.x*p2.x, p1.y*p2.y);
}

inline cocos2d::CCPoint accpMult(cocos2d::CCPoint p, float scale) {
    return cocos2d::CCPoint(p.x*scale, p.y*scale);
}

inline cocos2d::CCSize accsMult(cocos2d::CCSize size, float scale) {
    return cocos2d::CCSize(size.width*scale, size.height*scale);
}

APS_END_NAMESPACE

#endif





