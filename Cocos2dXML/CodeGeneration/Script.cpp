//
//  Script.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 2/1/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Script.h"

#pragma mark - NoPL callbacks

//TODO: set up callbacks

#pragma mark - Script

void Script::load()
{
	//TODO: create a separate script manager class
	//TODO: get events / listeners working
	
	//TODO: pre-load the script in the manager
	
	if(runListener == "")
		runScript();
}

void Script::unload()
{
	
}

void Script::runScript()
{
	//TODO: run the script
}
