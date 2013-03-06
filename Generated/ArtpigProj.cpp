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
	
	//calculate the scale that we should use to display the APS project
	cocos2d::CCSize windowSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	cocos2d::CCSize projSize = node->getContentSize();
	float newScale = windowSize.width/projSize.height;//projSize height and width are switched because rotation is always +90
	if(windowSize.height/projSize.width > newScale)
		newScale = windowSize.height/projSize.width;
	
	//make the Cocos2dXML object reflect the properties set by the APS project
	setPosition(node->getPosition());
	setRotation(node->getRotation());
	setAnchorPoint(node->getAnchorPoint());
	setSize(cocos2d::CCPoint(node->getContentSize().width, node->getContentSize().height));
	setScale(cocos2d::CCPoint(newScale, newScale));
	
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