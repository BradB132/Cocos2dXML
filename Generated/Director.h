//
//  Director.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#import "Director_Base.h"

class Scene;

class Director : public Director_Base
{
public:
	
	static Director* sharedDirector();
	
	virtual void load();
	virtual void attributeDidChange(int attributeID);
	
	//scene management
	virtual bool switchToScene(SceneReference* ref, Transition* trans, bool push);
	
protected:
	
	Scene* currentScene;
};

#endif //end __DIRECTOR_H__
