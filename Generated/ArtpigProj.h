//
//  ArtpigProj.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 3/3/13.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef __ARTPIGPROJ_H__
#define __ARTPIGPROJ_H__

#include "ArtpigProj_Base.h"
#include "artpig.h"

class ArtpigProj : public ArtpigProj_Base, public artpig::APSActionObserver
{
public:
	
	virtual void load();
	virtual void unload();
	
	void play();
	
	//implementing APSActionObserver
	virtual void willStartAction(artpig::APSAction *action);
    virtual void didFinishAction(artpig::APSAction *action);
	
protected:
	
	artpig::APSSymbol* symbol;
};

#endif //end __ARTPIGPROJ_H__
