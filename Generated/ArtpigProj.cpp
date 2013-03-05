//
//  ArtpigProj.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 3/3/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "ArtpigProj.h"

void ArtpigProj::play()
{
	symbol->triggerPrologueActionGroups();
}

void ArtpigProj::load()
{
	//allocate new symbol
	artpig::APSResourceManager* manager = artpig::APSResourceManager::getResourceManagerForProjectId(projectID.c_str());
	symbol = manager->newSymbol();

	//preload data to run animation without delay.
	symbol->preloadData();
	
	//set our node to be the symbol's root node
	node = symbol->getRootNode();
	
	ArtpigProj_Base::load();
	
	//are we going to auto-play?
	if(startListener == "")
		play();
}

void ArtpigProj::unload()
{
	//null out the node so that the parent class doesn't double-free it
	node = NULL;
	
	if(symbol)
	{
		delete symbol;
		symbol = NULL;
	}
	
	ArtpigProj_Base::unload();
}