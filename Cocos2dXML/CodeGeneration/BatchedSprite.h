//
//  BatchedSprite.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __BATCHEDSPRITE_H__
#define __BATCHEDSPRITE_H__

#import "BatchedSprite_Base.h"

class BatchedSprite : public BatchedSprite_Base
{
public:
	virtual void load();
	
	virtual void attributeDidChange(int attributeID);
};

#endif //end __BATCHEDSPRITE_H__
