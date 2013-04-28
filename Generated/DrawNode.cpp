//
//  DrawNode.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 4/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "DrawNode.h"

void DrawNode::load()
{
	if(!node)
	{
		node = cocos2d::CCDrawNode::create();
		if(node)
			node->retain();
	}
	
	DrawNode_Base::load();
}

NoPL_FunctionValue DrawNode::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	if(node)
	{
		//all draw functions either take 0 args or pairs of numbers
		if(argc == 0)
		{
			if(!strcmp(functionName, "clear"))
			{
				((cocos2d::CCDrawNode*)node)->clear();
				returnVal.type = NoPL_DataType_Void;
			}
			else if(!strcmp(functionName, "finishPolygon"))
			{
				((cocos2d::CCDrawNode*)node)->drawPolygon(&(polygonVerts[0]), polygonVerts.size(),
														  Cocos2dXMLColor_To_ccColor4F(fillColor),
														  lineWidth,
														  Cocos2dXMLColor_To_ccColor4F(lineColor));
				polygonVerts.clear();
				returnVal.type = NoPL_DataType_Void;
			}
			else if(!strcmp(functionName, "restartPolygon"))
			{
				polygonVerts.clear();
				returnVal.type = NoPL_DataType_Void;
			}
		}
		else if(argc % 2 == 0)
		{
			bool allNumbers = true;
			for(int i = 0; i < argc; i++)
			{
				if(argv[i].type != NoPL_DataType_Number)
				{
					allNumbers = false;
					break;
				}
			}
			if(allNumbers)
			{
				if(argc % 2 == 0 && !strcmp(functionName, "drawPolygon"))
				{
					//assemble an array of CCPoints
					unsigned int vertexCount = argc/2;
					cocos2d::CCPoint* points = (cocos2d::CCPoint*)malloc(sizeof(cocos2d::CCPoint)*vertexCount);
					for(int i = 0; i < vertexCount; i++)
					{
						points[i].x = argv[i*2].numberValue;
						points[i].y = argv[i*2+1].numberValue;
					}
					
					((cocos2d::CCDrawNode*)node)->drawPolygon(points, vertexCount,
															  Cocos2dXMLColor_To_ccColor4F(fillColor),
															  lineWidth,
															  Cocos2dXMLColor_To_ccColor4F(lineColor));
					returnVal.type = NoPL_DataType_Void;
					
					free(points);
				}
				else if(argc == 2)
				{
					if(!strcmp(functionName, "drawDot"))
					{
						((cocos2d::CCDrawNode*)node)->drawDot(cocos2d::CCPoint(argv[0].numberValue, argv[1].numberValue),
															  lineWidth,
															  Cocos2dXMLColor_To_ccColor4F(lineColor));
						returnVal.type = NoPL_DataType_Void;
					}
					else if(!strcmp(functionName, "addPointToPolygon"))
					{
						polygonVerts.push_back(cocos2d::CCPoint(argv[0].numberValue, argv[1].numberValue));
						returnVal.type = NoPL_DataType_Void;
					}
				}
				else if(argc == 4 && !strcmp(functionName, "drawSegment"))
				{
					((cocos2d::CCDrawNode*)node)->drawSegment(cocos2d::CCPoint(argv[0].numberValue, argv[1].numberValue),
															  cocos2d::CCPoint(argv[2].numberValue, argv[3].numberValue),
															  lineWidth,
															  Cocos2dXMLColor_To_ccColor4F(lineColor));
					returnVal.type = NoPL_DataType_Void;
				}
			}
		}
	}
	
	if(returnVal.type == NoPL_DataType_Uninitialized)
		return Node_Base::evaluateFunction(functionName, argv, argc);
	return returnVal;
}

cocos2d::ccColor4F DrawNode::Cocos2dXMLColor_To_ccColor4F(Cocos2dXMLColor color)
{
	cocos2d::ccColor4F returnColor;
	returnColor.r = color.rgb.r/255.0f;
	returnColor.g = color.rgb.g/255.0f;
	returnColor.b = color.rgb.b/255.0f;
	returnColor.a = color.a/255.0f;
	return returnColor;
}

bool DrawNode::setSrcBlend(srcBlendFunc newSrcBlend)
{
	if(node)
	{
		cocos2d::CCDrawNode* drawNode = (cocos2d::CCDrawNode*)node;
		cocos2d::ccBlendFunc newFunc = drawNode->getBlendFunc();
		newFunc.src = srcBlend;
		drawNode->setBlendFunc(newFunc);
	}
	return DrawNode_Base::setSrcBlend(newSrcBlend);
}

bool DrawNode::setDstBlend(dstBlendFunc newDstBlend)
{
	if(node)
	{
		cocos2d::CCDrawNode* drawNode = (cocos2d::CCDrawNode*)node;
		cocos2d::ccBlendFunc newFunc = drawNode->getBlendFunc();
		newFunc.dst = dstBlend;
		drawNode->setBlendFunc(newFunc);
	}
	return DrawNode_Base::setDstBlend(newDstBlend);
}
