//
//  Node.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __NODE_H__
#define __NODE_H__

#import "Node_Base.h"
#include "base_nodes/CCNode.h"

class Node : public Node_Base
{
public:
	
	Node();
	~Node();
	
	virtual void load();
	virtual void unload();
	
	virtual void attributeDidChange(int attributeID);
	
	virtual cocos2d::CCNode* getCCNode();
	
protected:
	
	cocos2d::CCNode* node;
	
};

#endif //end __NODE_H__
