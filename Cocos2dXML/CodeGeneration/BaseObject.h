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
	
	virtual void load();
	virtual void unload();
	
};

#endif //end __BASEOBJECT_H__
