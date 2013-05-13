//
//  Animation.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Animation.h"
#include "Sprite.h"

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
	
	cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
	center->removeObserver(this);
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
			
			//set up a format string 
			char formattedString[sequence.length()+10];
			int replaceIndex = format.find('#');
			if(replaceIndex == std::string::npos)
				return;
			std::string formatterString = format.replace(replaceIndex, 1, "%d");
			
			//iterate over all of the expressions in the sequence string
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
				
				//check if this expression is a span of numbers or a multiple of the same number
				if(expression.find(spanDelimiter) != std::string::npos)
				{
					//this expression contains the span character, get the indices included in the span
					int spanIndex = expression.find(spanDelimiter);
					int startNum = atoi(expression.substr(0,spanIndex).c_str());
					int endNum = atoi(expression.substr(spanIndex+1).c_str());
					
					//this loop should support counting up or down
					int incrementor = (endNum > startNum) ? 1 : -1;
					for(int i = startNum; i-incrementor != endNum; i += incrementor)
					{
						//add each frame in the span
						sprintf(formattedString, formatterString.c_str(), i);
						cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(formattedString);
						frameList->addObject(frame);
					}
				}
				else if(expression.find(spanMultiplier) != std::string::npos)
				{
					//this expression contains the multiplier character, get the index and multiplier
					int multIndex = expression.find(spanMultiplier);
					int frameIndex = atoi(expression.substr(0,multIndex).c_str());
					int repeats = atoi(expression.substr(multIndex+1).c_str());
					
					//add the same frame multiple times
					sprintf(formattedString, formatterString.c_str(), frameIndex);
					cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(formattedString);
					for(int i = 0; i < repeats; i++)
						frameList->addObject(frame);
				}
				else
				{
					//this is not a special kind of expression, just a single frame index
					int frameIndex = atoi(expression.c_str());
					sprintf(formattedString, formatterString.c_str(), frameIndex);
					cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(formattedString);
					frameList->addObject(frame);
				}
				
				if(shouldBreak)
					break;
				
				delimitIndex = nextIndex+1;
			}
		}
			return;
		case id_Animation_startListener:
		{
			cocos2d::CCNotificationCenter* center = cocos2d::CCNotificationCenter::sharedNotificationCenter();
			
			//remove self from any notifications
			center->removeObserver(this);
			
			//listen to the new notification
			center->addObserver(this,
								cocos2d::SEL_NoteHandler(&Animation::handleAnimateEvent),
								startListener.c_str(),
								getRootObject());
		}
			return;
		case id_Animation_target:
		case id_Animation_format:
		case id_Animation_fps:
		case id_Animation_loops:
			return;
	}
	Animation_Base::attributeDidChange(attributeID);
}

void Animation::handleAnimateEvent(const char* noteName, cocos2d::CCDictionary* params)
{
	this->animate();
}

void Animation::animate()
{
	Sprite* targetSprite = dynamic_cast<Sprite*>(objectForID(target));
	if(targetSprite)
	{
		cocos2d::CCAnimation* animation = cocos2d::CCAnimation::createWithSpriteFrames(frameList, 1.0/fps);
		animation->setLoops(loops);
		animation->setRestoreOriginalFrame(restoreOriginalFrame);
		((cocos2d::CCSprite*)targetSprite->getCCNode())->runAction(cocos2d::CCAnimate::create(animation));
	}
}
