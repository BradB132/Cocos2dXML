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
	virtual void unload();
	virtual void attributeDidChange(int attributeID);
	virtual void update(float dt);
	
	//scene management
	SceneReference* sceneRefForID(std::string idString);
	Transition* transitionForID(std::string idString);
	virtual bool switchToScene(SceneReference* ref, Transition* trans, bool push);
	virtual void popScene();
	virtual void popToRootScene();
	
protected:
	
	void discardTopScene();
	
	cocos2d::CCArray* sceneStack;
	cocos2d::CCArray* discardedScenes;
	
};

#endif //end __DIRECTOR_H__
