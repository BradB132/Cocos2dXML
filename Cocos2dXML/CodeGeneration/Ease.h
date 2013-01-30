//
//  Ease.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __EASE_H__
#define __EASE_H__

#import "Ease_Base.h"

class Ease : public Ease_Base
{
public:
	
	virtual void attributeDidChange(int attributeID);
	
protected:
	
	virtual cocos2d::CCAction* createActionObject();
};

#endif //end __EASE_H__
