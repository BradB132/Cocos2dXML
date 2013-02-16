//
//  Animation.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Animation.h"

void Animation::load()
{
	refreshAllAttributes();
	
	if(startListener == "")
		animate();
}

void Animation::unload()
{
	if(frameList)
	{
		frameList->release();
		frameList = NULL;
	}
}

void Animation::attributeDidChange(int attributeID)
{
	switch (attributeID)
	{
		case id_Animation_sequence:
		{
			//create a new array for holding frames
			if(frameList)
				frameList->release();
			frameList = cocos2d::CCArray::create();
			frameList->retain();
			
			/*
			 std::string sequence = "1,2,3-4,6*3";
			 
			 char delimiter = ',';
			 char spanDelimiter = '-';
			 char spanMultiplier = '*';
			 int delimitIndex = 0;
			 while(true)
			 {
			 //get the next expression in the sequence
			 int nextIndex = sequence.find(delimiter, delimitIndex);
			 bool shouldBreak = (nextIndex == std::string::npos);
			 std::string expression;
			 if(shouldBreak)
			 expression = sequence.substr(delimitIndex);
			 else
			 expression = sequence.substr(delimitIndex, nextIndex-delimitIndex);
			 
			 if(expression.find(spanDelimiter) != std::string::npos)
			 {
			 int spanIndex = expression.find(spanDelimiter);
			 int startNum = atoi(expression.substr(0,spanIndex).c_str());
			 int endNum = atoi(expression.substr(spanIndex+1).c_str());
			 
			 if(startNum > endNum)
			 {
			 
			 }
			 else
			 {
			 
			 }
			 }
			 
			 if(shouldBreak)
			 break;
			 
			 delimitIndex = nextIndex+1;
			 }
			*/
		}
			return;
		case id_Animation_startListener:
			//TODO: subscribe
			return;
		case id_Animation_target:
		case id_Animation_format:
		case id_Animation_fps:
		case id_Animation_loops:
			return;
	}
	Animation_Base::attributeDidChange(attributeID);
}

void Animation::animate()
{
	cocos2d::CCSprite* targetSprite = dynamic_cast<cocos2d::CCSprite*>(objectForID(target));
	if(targetSprite)
	{
		
	}
}
