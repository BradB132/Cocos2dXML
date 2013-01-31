//
//  Sequence.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#import "Sequence_Base.h"

class Sequence : public Sequence_Base
{
protected:
	
	virtual void createActionObject(cocos2d::CCAction** outAction);
};

#endif //end __SEQUENCE_H__
