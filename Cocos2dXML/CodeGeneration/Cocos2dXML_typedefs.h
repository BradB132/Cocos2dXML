//
//  Cocos2dXML_typedefs.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __COCOS2DXML_TYPEDEFS_H__
#define __COCOS2DXML_TYPEDEFS_H__

#include <iostream>
#include "cocos2d.h"

//some specialized types here
typedef std::string Cocos2dXMLEvent;
typedef std::string Cocos2dXMLEventListener;
typedef std::string Cocos2dXMLFilePath;

typedef struct
{
	cocos2d::ccColor3B rgb;
	unsigned char a;
}Cocos2dXMLColor;

//handle conversions from strings
cocos2d::ccColor3B string_to_ccColor3B(const char* colorString);
Cocos2dXMLColor string_to_Cocos2dXMLColor(const char* colorString);
bool string_to_bool(char* boolString);
cocos2d::CCPoint string_to_CCPoint(char* pointString);

//utility functions for handling types
bool isKindOfClass(const char* instanceTypeName, const char* desiredTypeName);
cocos2d::CCObject* newObjectOfType(const char* typeName);

#endif //end __COCOS2DXML_TYPEDEFS_H__

