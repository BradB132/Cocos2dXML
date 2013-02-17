//
//  Animation.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#import "Animation_Base.h"

class Animation : public Animation_Base
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual void animate();
	
	virtual void attributeDidChange(int attributeID);
	
protected:
	
	void handleAnimateEvent(const char* noteName, cocos2d::CCDictionary* params);
	
	//cache the array sequence of frames
	cocos2d::CCArray* frameList;
};

#endif //end __ANIMATION_H__
