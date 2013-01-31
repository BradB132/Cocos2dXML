//
//  Cocos2dXML_enums.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/31/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __COCOS2DXML_ENUMS_H__
#define __COCOS2DXML_ENUMS_H__

#include <iostream>
#include "cocos2d.h"

#pragma mark - Enum declarations

typedef enum
{
	srcBlendFunc_zero = GL_ZERO,
	srcBlendFunc_one = GL_ONE,
	srcBlendFunc_sourceColor = GL_SRC_COLOR,
	srcBlendFunc_sourceMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
	srcBlendFunc_destinationColor = GL_DST_COLOR,
	srcBlendFunc_oneMinuesDestinationColor = GL_ONE_MINUS_DST_COLOR,
	srcBlendFunc_sourceAlpha = GL_SRC_ALPHA,
	srcBlendFunc_oneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
	srcBlendFunc_destinationAlpha = GL_DST_ALPHA,
	srcBlendFunc_oneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
	srcBlendFunc_constantColor = GL_CONSTANT_COLOR,
	srcBlendFunc_oneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	srcBlendFunc_constantAlpha = GL_CONSTANT_ALPHA,
	srcBlendFunc_oneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	srcBlendFunc_sourceAlphaSaturate = GL_SRC_ALPHA_SATURATE,
}srcBlendFunc;

typedef enum
{
	dstBlendFunc_zero = GL_ZERO,
	dstBlendFunc_one = GL_ONE,
	dstBlendFunc_sourceColor = GL_SRC_COLOR,
	dstBlendFunc_oneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
	dstBlendFunc_destinationColor = GL_DST_COLOR,
	dstBlendFunc_oneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
	dstBlendFunc_sourceAlpha = GL_SRC_ALPHA,
	dstBlendFunc_oneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
	dstBlendFunc_destinationAlpha = GL_DST_ALPHA,
	dstBlendFunc_oneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
	dstBlendFunc_constantColor = GL_CONSTANT_COLOR,
	dstBlendFunc_oneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	dstBlendFunc_constantAlpha = GL_CONSTANT_ALPHA,
	dstBlendFunc_oneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
}dstBlendFunc;

typedef enum
{
	ease_in,
	ease_out,
	ease_inOut,
	ease_eponentialIn,
	ease_eponentialOut,
	ease_eponentialInOut,
	ease_sineIn,
	ease_sineOut,
	ease_sineInOut,
	ease_elasticIn,
	ease_elasticOut,
	ease_elasticInOut,
	ease_bounceIn,
	ease_bounceOut,
	ease_bounceInOut,
	ease_backIn,
	ease_backOut,
	ease_backInOut,
}ease;

typedef enum
{
	horizontalTextAlign_left = cocos2d::kCCTextAlignmentLeft,
	horizontalTextAlign_center = cocos2d::kCCTextAlignmentCenter,
	horizontalTextAlign_right = cocos2d::kCCTextAlignmentRight,
}horizontalTextAlign;

typedef enum
{
	verticalTextAlign_top = cocos2d::kCCVerticalTextAlignmentTop,
	verticalTextAlign_center = cocos2d::kCCVerticalTextAlignmentCenter,
	verticalTextAlign_bottom = cocos2d::kCCVerticalTextAlignmentBottom,
}verticalTextAlign;

typedef enum
{
	transition_none,
	transition_rotoZoom,
	transition_jumpZoom,
	transition_moveInL,
	transition_moveInR,
	transition_moveInT,
	transition_moveInB,
	transition_slideInL,
	transition_slideInR,
	transition_slideInT,
	transition_slideInB,
	transition_shrinkGrow,
	transition_flipX,
	transition_flipY,
	transition_flipAngular,
	transition_zoomFlipX,
	transition_zoomFlipY,
	transition_zoomFlipAngular,
	transition_fade,
	transition_crossFade,
	transition_turnOffTiles,
	transition_splitCols,
	transition_splitRows,
	transition_fadeTR,
	transition_fadeBL,
	transition_fadeUp,
	transition_fadeDown,
	transition_pageTurn,
	transition_progressRadialCW,
	transition_progressRadialCCW,
	transition_progressHorizontal,
	transition_progressVertical,
	transition_progressInOut,
	transition_progressOutIn,
}transition;

#pragma mark - Enum conversions

srcBlendFunc string_to_srcBlendFunc(std::string enumString);
std::string srcBlendFunc_to_string(srcBlendFunc enumValue);

dstBlendFunc string_to_dstBlendFunc(std::string enumString);
std::string dstBlendFunc_to_string(dstBlendFunc enumValue);

ease string_to_ease(std::string enumString);
std::string ease_to_string(ease enumValue);

horizontalTextAlign string_to_horizontalTextAlign(std::string enumString);
std::string horizontalTextAlign_to_string(horizontalTextAlign enumValue);

verticalTextAlign string_to_verticalTextAlign(std::string enumString);
std::string verticalTextAlign_to_string(verticalTextAlign enumValue);

transition string_to_transition(std::string enumString);
std::string transition_to_string(transition enumValue);

#endif //end __COCOS2DXML_ENUMS_H__
