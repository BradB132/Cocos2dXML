//
//  Move.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __MOVE_H__
#define __MOVE_H__

#import "Move_Base.h"

class Move : public Move_Base
{
protected:
	
	virtual void createActionObject(cocos2d::CCAction** outAction);
};

#endif //end __MOVE_H__
