//
//  Scene.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __SCENE_H__
#define __SCENE_H__

#import "Scene_Base.h"

class Scene : public Scene_Base
{
public:
	
	virtual void load();
	virtual void unload();
	
	virtual void visitLoad();
	
	virtual void addToSceneMap(BaseObject* obj);
	virtual void removeFromSceneMap(BaseObject* obj);
	virtual BaseObject* objectFromMap(std::string objectID);
	
	virtual NoPL_FunctionValue evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc);
	
	virtual void update(float dt);
	virtual void attributeDidChange(int attributeID);
	
protected:
	
	std::map<std::string, BaseObject*> objectMap;
	
};

#endif //end __SCENE_H__
