//
//  DrawNode.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 4/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __DRAWNODE_H__
#define __DRAWNODE_H__

#include "DrawNode_Base.h"

class DrawNode : public DrawNode_Base
{
public:
	virtual void load();
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
	
	virtual bool setSrcBlend(srcBlendFunc newSrcBlend);
	virtual bool setDstBlend(dstBlendFunc newDstBlend);
	
	//color helper function
	cocos2d::ccColor4F Cocos2dXMLColor_To_ccColor4F(Cocos2dXMLColor color);
	
protected:
	
	std::vector<cocos2d::CCPoint> polygonVerts;
};

#endif //end __DRAWNODE_H__
