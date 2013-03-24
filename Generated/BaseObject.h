//
//  BaseObject.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#import "BaseObject_Base.h"

class BaseObject : public BaseObject_Base
{
public:
	
	BaseObject();
	
	virtual BaseObject* getRootObject();
	virtual BaseObject* objectForID(std::string objectID);
	
	//convenience functions for events
	void postEvent(std::string eventName);
	void postEvent(std::string eventName, cocos2d::CCDictionary* args);
	void listenForEvent(std::string eventName, cocos2d::SEL_NoteHandler selector);
	void stopListeningToEvent(std::string eventName);
	void stopListeningToAllEvents();
	
	virtual void load();
	virtual void unload();
	
	virtual bool setId(std::string newId);
	
private:
	
	bool alreadySetID;
};

#endif //end __BASEOBJECT_H__
