#include "Cocos2dXML_enums.h"

srcBlendFunc string_to_srcBlendFunc(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "zero"))
		return srcBlendFunc_zero;
	else if(!strcmp(enumStringC, "one"))
		return srcBlendFunc_one;
	else if(!strcmp(enumStringC, "sourceColor"))
		return srcBlendFunc_sourceColor;
	else if(!strcmp(enumStringC, "sourceMinusSourceColor"))
		return srcBlendFunc_sourceMinusSourceColor;
	else if(!strcmp(enumStringC, "destinationColor"))
		return srcBlendFunc_destinationColor;
	else if(!strcmp(enumStringC, "oneMinuesDestinationColor"))
		return srcBlendFunc_oneMinuesDestinationColor;
	else if(!strcmp(enumStringC, "sourceAlpha"))
		return srcBlendFunc_sourceAlpha;
	else if(!strcmp(enumStringC, "oneMinusSourceAlpha"))
		return srcBlendFunc_oneMinusSourceAlpha;
	else if(!strcmp(enumStringC, "destinationAlpha"))
		return srcBlendFunc_destinationAlpha;
	else if(!strcmp(enumStringC, "oneMinusDestinationAlpha"))
		return srcBlendFunc_oneMinusDestinationAlpha;
	else if(!strcmp(enumStringC, "constantColor"))
		return srcBlendFunc_constantColor;
	else if(!strcmp(enumStringC, "oneMinusConstantColor"))
		return srcBlendFunc_oneMinusConstantColor;
	else if(!strcmp(enumStringC, "constantAlpha"))
		return srcBlendFunc_constantAlpha;
	else if(!strcmp(enumStringC, "oneMinusConstantAlpha"))
		return srcBlendFunc_oneMinusConstantAlpha;
	else if(!strcmp(enumStringC, "sourceAlphaSaturate"))
		return srcBlendFunc_sourceAlphaSaturate;
	return (srcBlendFunc)-1;
}

std::string srcBlendFunc_to_string(srcBlendFunc enumValue)
{
	switch(enumValue)
	{
		case srcBlendFunc_zero:
			return "zero";
		case srcBlendFunc_one:
			return "one";
		case srcBlendFunc_sourceColor:
			return "sourceColor";
		case srcBlendFunc_sourceMinusSourceColor:
			return "sourceMinusSourceColor";
		case srcBlendFunc_destinationColor:
			return "destinationColor";
		case srcBlendFunc_oneMinuesDestinationColor:
			return "oneMinuesDestinationColor";
		case srcBlendFunc_sourceAlpha:
			return "sourceAlpha";
		case srcBlendFunc_oneMinusSourceAlpha:
			return "oneMinusSourceAlpha";
		case srcBlendFunc_destinationAlpha:
			return "destinationAlpha";
		case srcBlendFunc_oneMinusDestinationAlpha:
			return "oneMinusDestinationAlpha";
		case srcBlendFunc_constantColor:
			return "constantColor";
		case srcBlendFunc_oneMinusConstantColor:
			return "oneMinusConstantColor";
		case srcBlendFunc_constantAlpha:
			return "constantAlpha";
		case srcBlendFunc_oneMinusConstantAlpha:
			return "oneMinusConstantAlpha";
		case srcBlendFunc_sourceAlphaSaturate:
			return "sourceAlphaSaturate";
		default:
			return "";
	}
}
dstBlendFunc string_to_dstBlendFunc(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "zero"))
		return dstBlendFunc_zero;
	else if(!strcmp(enumStringC, "one"))
		return dstBlendFunc_one;
	else if(!strcmp(enumStringC, "sourceColor"))
		return dstBlendFunc_sourceColor;
	else if(!strcmp(enumStringC, "oneMinusSourceColor"))
		return dstBlendFunc_oneMinusSourceColor;
	else if(!strcmp(enumStringC, "destinationColor"))
		return dstBlendFunc_destinationColor;
	else if(!strcmp(enumStringC, "oneMinusDestinationColor"))
		return dstBlendFunc_oneMinusDestinationColor;
	else if(!strcmp(enumStringC, "sourceAlpha"))
		return dstBlendFunc_sourceAlpha;
	else if(!strcmp(enumStringC, "oneMinusSourceAlpha"))
		return dstBlendFunc_oneMinusSourceAlpha;
	else if(!strcmp(enumStringC, "destinationAlpha"))
		return dstBlendFunc_destinationAlpha;
	else if(!strcmp(enumStringC, "oneMinusDestinationAlpha"))
		return dstBlendFunc_oneMinusDestinationAlpha;
	else if(!strcmp(enumStringC, "constantColor"))
		return dstBlendFunc_constantColor;
	else if(!strcmp(enumStringC, "oneMinusConstantColor"))
		return dstBlendFunc_oneMinusConstantColor;
	else if(!strcmp(enumStringC, "constantAlpha"))
		return dstBlendFunc_constantAlpha;
	else if(!strcmp(enumStringC, "oneMinusConstantAlpha"))
		return dstBlendFunc_oneMinusConstantAlpha;
	return (dstBlendFunc)-1;
}

std::string dstBlendFunc_to_string(dstBlendFunc enumValue)
{
	switch(enumValue)
	{
		case dstBlendFunc_zero:
			return "zero";
		case dstBlendFunc_one:
			return "one";
		case dstBlendFunc_sourceColor:
			return "sourceColor";
		case dstBlendFunc_oneMinusSourceColor:
			return "oneMinusSourceColor";
		case dstBlendFunc_destinationColor:
			return "destinationColor";
		case dstBlendFunc_oneMinusDestinationColor:
			return "oneMinusDestinationColor";
		case dstBlendFunc_sourceAlpha:
			return "sourceAlpha";
		case dstBlendFunc_oneMinusSourceAlpha:
			return "oneMinusSourceAlpha";
		case dstBlendFunc_destinationAlpha:
			return "destinationAlpha";
		case dstBlendFunc_oneMinusDestinationAlpha:
			return "oneMinusDestinationAlpha";
		case dstBlendFunc_constantColor:
			return "constantColor";
		case dstBlendFunc_oneMinusConstantColor:
			return "oneMinusConstantColor";
		case dstBlendFunc_constantAlpha:
			return "constantAlpha";
		case dstBlendFunc_oneMinusConstantAlpha:
			return "oneMinusConstantAlpha";
		default:
			return "";
	}
}
ease string_to_ease(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "in"))
		return ease_in;
	else if(!strcmp(enumStringC, "out"))
		return ease_out;
	else if(!strcmp(enumStringC, "inOut"))
		return ease_inOut;
	else if(!strcmp(enumStringC, "eponentialIn"))
		return ease_eponentialIn;
	else if(!strcmp(enumStringC, "eponentialOut"))
		return ease_eponentialOut;
	else if(!strcmp(enumStringC, "eponentialInOut"))
		return ease_eponentialInOut;
	else if(!strcmp(enumStringC, "sineIn"))
		return ease_sineIn;
	else if(!strcmp(enumStringC, "sineOut"))
		return ease_sineOut;
	else if(!strcmp(enumStringC, "sineInOut"))
		return ease_sineInOut;
	else if(!strcmp(enumStringC, "elasticIn"))
		return ease_elasticIn;
	else if(!strcmp(enumStringC, "elasticOut"))
		return ease_elasticOut;
	else if(!strcmp(enumStringC, "elasticInOut"))
		return ease_elasticInOut;
	else if(!strcmp(enumStringC, "bounceIn"))
		return ease_bounceIn;
	else if(!strcmp(enumStringC, "bounceOut"))
		return ease_bounceOut;
	else if(!strcmp(enumStringC, "bounceInOut"))
		return ease_bounceInOut;
	else if(!strcmp(enumStringC, "backIn"))
		return ease_backIn;
	else if(!strcmp(enumStringC, "backOut"))
		return ease_backOut;
	else if(!strcmp(enumStringC, "backInOut"))
		return ease_backInOut;
	return (ease)-1;
}

std::string ease_to_string(ease enumValue)
{
	switch(enumValue)
	{
		case ease_in:
			return "in";
		case ease_out:
			return "out";
		case ease_inOut:
			return "inOut";
		case ease_eponentialIn:
			return "eponentialIn";
		case ease_eponentialOut:
			return "eponentialOut";
		case ease_eponentialInOut:
			return "eponentialInOut";
		case ease_sineIn:
			return "sineIn";
		case ease_sineOut:
			return "sineOut";
		case ease_sineInOut:
			return "sineInOut";
		case ease_elasticIn:
			return "elasticIn";
		case ease_elasticOut:
			return "elasticOut";
		case ease_elasticInOut:
			return "elasticInOut";
		case ease_bounceIn:
			return "bounceIn";
		case ease_bounceOut:
			return "bounceOut";
		case ease_bounceInOut:
			return "bounceInOut";
		case ease_backIn:
			return "backIn";
		case ease_backOut:
			return "backOut";
		case ease_backInOut:
			return "backInOut";
		default:
			return "";
	}
}
horizontalTextAlign string_to_horizontalTextAlign(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "left"))
		return horizontalTextAlign_left;
	else if(!strcmp(enumStringC, "center"))
		return horizontalTextAlign_center;
	else if(!strcmp(enumStringC, "right"))
		return horizontalTextAlign_right;
	return (horizontalTextAlign)-1;
}

std::string horizontalTextAlign_to_string(horizontalTextAlign enumValue)
{
	switch(enumValue)
	{
		case horizontalTextAlign_left:
			return "left";
		case horizontalTextAlign_center:
			return "center";
		case horizontalTextAlign_right:
			return "right";
		default:
			return "";
	}
}
verticalTextAlign string_to_verticalTextAlign(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "top"))
		return verticalTextAlign_top;
	else if(!strcmp(enumStringC, "center"))
		return verticalTextAlign_center;
	else if(!strcmp(enumStringC, "bottom"))
		return verticalTextAlign_bottom;
	return (verticalTextAlign)-1;
}

std::string verticalTextAlign_to_string(verticalTextAlign enumValue)
{
	switch(enumValue)
	{
		case verticalTextAlign_top:
			return "top";
		case verticalTextAlign_center:
			return "center";
		case verticalTextAlign_bottom:
			return "bottom";
		default:
			return "";
	}
}
transition string_to_transition(std::string enumString)
{
	const char* enumStringC = enumString.c_str();
	if(!strcmp(enumStringC, "none"))
		return transition_none;
	else if(!strcmp(enumStringC, "rotoZoom"))
		return transition_rotoZoom;
	else if(!strcmp(enumStringC, "jumpZoom"))
		return transition_jumpZoom;
	else if(!strcmp(enumStringC, "moveInL"))
		return transition_moveInL;
	else if(!strcmp(enumStringC, "moveInR"))
		return transition_moveInR;
	else if(!strcmp(enumStringC, "moveInT"))
		return transition_moveInT;
	else if(!strcmp(enumStringC, "moveInB"))
		return transition_moveInB;
	else if(!strcmp(enumStringC, "slideInL"))
		return transition_slideInL;
	else if(!strcmp(enumStringC, "slideInR"))
		return transition_slideInR;
	else if(!strcmp(enumStringC, "slideInT"))
		return transition_slideInT;
	else if(!strcmp(enumStringC, "slideInB"))
		return transition_slideInB;
	else if(!strcmp(enumStringC, "shrinkGrow"))
		return transition_shrinkGrow;
	else if(!strcmp(enumStringC, "flipX"))
		return transition_flipX;
	else if(!strcmp(enumStringC, "flipY"))
		return transition_flipY;
	else if(!strcmp(enumStringC, "flipAngular"))
		return transition_flipAngular;
	else if(!strcmp(enumStringC, "zoomFlipX"))
		return transition_zoomFlipX;
	else if(!strcmp(enumStringC, "zoomFlipY"))
		return transition_zoomFlipY;
	else if(!strcmp(enumStringC, "zoomFlipAngular"))
		return transition_zoomFlipAngular;
	else if(!strcmp(enumStringC, "fade"))
		return transition_fade;
	else if(!strcmp(enumStringC, "crossFade"))
		return transition_crossFade;
	else if(!strcmp(enumStringC, "turnOffTiles"))
		return transition_turnOffTiles;
	else if(!strcmp(enumStringC, "splitCols"))
		return transition_splitCols;
	else if(!strcmp(enumStringC, "splitRows"))
		return transition_splitRows;
	else if(!strcmp(enumStringC, "fadeTR"))
		return transition_fadeTR;
	else if(!strcmp(enumStringC, "fadeBL"))
		return transition_fadeBL;
	else if(!strcmp(enumStringC, "fadeUp"))
		return transition_fadeUp;
	else if(!strcmp(enumStringC, "fadeDown"))
		return transition_fadeDown;
	else if(!strcmp(enumStringC, "pageTurn"))
		return transition_pageTurn;
	else if(!strcmp(enumStringC, "progressRadialCW"))
		return transition_progressRadialCW;
	else if(!strcmp(enumStringC, "progressRadialCCW"))
		return transition_progressRadialCCW;
	else if(!strcmp(enumStringC, "progressHorizontal"))
		return transition_progressHorizontal;
	else if(!strcmp(enumStringC, "progressVertical"))
		return transition_progressVertical;
	else if(!strcmp(enumStringC, "progressInOut"))
		return transition_progressInOut;
	else if(!strcmp(enumStringC, "progressOutIn"))
		return transition_progressOutIn;
	return (transition)-1;
}

std::string transition_to_string(transition enumValue)
{
	switch(enumValue)
	{
		case transition_none:
			return "none";
		case transition_rotoZoom:
			return "rotoZoom";
		case transition_jumpZoom:
			return "jumpZoom";
		case transition_moveInL:
			return "moveInL";
		case transition_moveInR:
			return "moveInR";
		case transition_moveInT:
			return "moveInT";
		case transition_moveInB:
			return "moveInB";
		case transition_slideInL:
			return "slideInL";
		case transition_slideInR:
			return "slideInR";
		case transition_slideInT:
			return "slideInT";
		case transition_slideInB:
			return "slideInB";
		case transition_shrinkGrow:
			return "shrinkGrow";
		case transition_flipX:
			return "flipX";
		case transition_flipY:
			return "flipY";
		case transition_flipAngular:
			return "flipAngular";
		case transition_zoomFlipX:
			return "zoomFlipX";
		case transition_zoomFlipY:
			return "zoomFlipY";
		case transition_zoomFlipAngular:
			return "zoomFlipAngular";
		case transition_fade:
			return "fade";
		case transition_crossFade:
			return "crossFade";
		case transition_turnOffTiles:
			return "turnOffTiles";
		case transition_splitCols:
			return "splitCols";
		case transition_splitRows:
			return "splitRows";
		case transition_fadeTR:
			return "fadeTR";
		case transition_fadeBL:
			return "fadeBL";
		case transition_fadeUp:
			return "fadeUp";
		case transition_fadeDown:
			return "fadeDown";
		case transition_pageTurn:
			return "pageTurn";
		case transition_progressRadialCW:
			return "progressRadialCW";
		case transition_progressRadialCCW:
			return "progressRadialCCW";
		case transition_progressHorizontal:
			return "progressHorizontal";
		case transition_progressVertical:
			return "progressVertical";
		case transition_progressInOut:
			return "progressInOut";
		case transition_progressOutIn:
			return "progressOutIn";
		default:
			return "";
	}
}
