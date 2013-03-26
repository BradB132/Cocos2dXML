//
//  Director.h
//  Cocos2dXML
//
//  Created by NoPLGenerator on 1/27/13.
//  Copyright (c) 2013. All rights reserved.
//

#include "Director.h"
#include "Scene.h"
#include "SceneReference.h"
#include "Transition.h"

static Director* _sharedDirector = NULL;

Director* Director::sharedDirector()
{
	return _sharedDirector;
}

void Director::load()
{
	//set self as a static director
	if(_sharedDirector)
		return;
	_sharedDirector = this;
	
	//set attributes of the director based on XML arguments
	refreshAllAttributes();
	
	if(SceneReferences->count() > 0)
	{
		//default to the first scene
		SceneReference* defaultScene = (SceneReference*)SceneReferences->objectAtIndex(0);
		switchToScene(defaultScene, NULL, false);
	}
}

void Director::attributeDidChange(int attributeID)
{
	switch (attributeID)
	{
		case id_Director_designedSize:
		{
			//get a reference to the director and openGL view so we can init them with XML values
			cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
			cocos2d::CCEGLView* glView = director->getOpenGLView();
			
			//set the content scale
			float smallerDesigned = (designedSize.x < designedSize.y) ? designedSize.x : designedSize.y;
			float smallerScreenSize = (glView->getFrameSize().width < glView->getFrameSize().height) ? glView->getFrameSize().width : glView->getFrameSize().height;
			int scaleFactor = (int)(smallerScreenSize/smallerDesigned);
			cocos2d::CCSize frame = glView->getFrameSize();
			glView->setDesignResolutionSize(frame.width/scaleFactor, frame.height/scaleFactor, kResolutionNoBorder);
			director->setContentScaleFactor(scaleFactor);
		}
			return;
		case id_Director_color:
		{
			cocos2d::CCDirector::sharedDirector()->setBackgroundColor(color);
		}
			return;
		case id_Director_displayStats:
		{
			cocos2d::CCDirector::sharedDirector()->setDisplayStats(displayStats);
		}
			return;
		case id_Director_fps:
		{
			cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0/fps);
		}
			return;
		case id_Director_depthTest:
		{
			cocos2d::CCDirector::sharedDirector()->setDepthTest(depthTest);
		}
			return;
		case id_Director_debug:
		{
			cocos2d::CCDirector::sharedDirector()->setDisplayOutlines(debug);
		}
			return;
	}
	Director_Base::attributeDidChange(attributeID);
}

SceneReference* Director::sceneRefForID(std::string idString)
{
	cocos2d::ccArray* arr = SceneReferences->data;
	for(int i = 0; i < arr->num; i++)
	{
		SceneReference* ref = (SceneReference*)arr->arr[i];
		if(ref->getId() == idString)
			return ref;
	}
	return NULL;
}

Transition* Director::transitionForID(std::string idString)
{
	cocos2d::ccArray* arr = Transitions->data;
	for(int i = 0; i < arr->num; i++)
	{
		Transition* trans = (Transition*)arr->arr[i];
		if(trans->getId() == idString)
			return trans;
	}
	return NULL;
}

bool Director::switchToScene(SceneReference* ref, Transition* trans, bool push)
{
	if(!ref)
		return false;
	
	//load the xml
	const char* fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(ref->getPath().c_str());
	xmlDocPtr xmlDocument = xmlReadFile(fullPath, NULL, XML_PARSE_XINCLUDE|XML_PARSE_NONET|XML_PARSE_NSCLEAN);
	if(!xmlDocument)
	{
		//TODO: bad XML file
		return false;
	}
	
	//dump our old scene if we have one
	//	if(currentScene)
	//		delete currentScene;
	
	//create the new scene using the XML
	currentScene = new Scene();
	currentScene->initWithXML(xmlDocument->children, NULL);
	currentScene->visitLoad();
	cocos2d::CCScene* ccScene = dynamic_cast<cocos2d::CCScene*>(currentScene->getCCNode());
	if(!ccScene)
		return false;
	
	//wrap this scene in a transition
	if(trans)
	{
		switch(trans->getType())
		{
			case transition_crossFade:
				ccScene = cocos2d::CCTransitionCrossFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fade:
				ccScene = cocos2d::CCTransitionFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeBL:
				ccScene = cocos2d::CCTransitionFadeBL::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeDown:
				ccScene = cocos2d::CCTransitionFadeDown::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeTR:
				ccScene = cocos2d::CCTransitionFadeTR::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeUp:
				ccScene = cocos2d::CCTransitionFadeUp::create(trans->getDuration(), ccScene);
				break;
			case transition_flipAngular:
				ccScene = cocos2d::CCTransitionFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_flipX:
				ccScene = cocos2d::CCTransitionFlipX::create(trans->getDuration(), ccScene);
				break;
			case transition_flipY:
				ccScene = cocos2d::CCTransitionFlipY::create(trans->getDuration(), ccScene);
				break;
			case transition_jumpZoom:
				ccScene = cocos2d::CCTransitionJumpZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInB:
				ccScene = cocos2d::CCTransitionMoveInB::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInL:
				ccScene = cocos2d::CCTransitionMoveInL::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInR:
				ccScene = cocos2d::CCTransitionMoveInR::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInT:
				ccScene = cocos2d::CCTransitionMoveInT::create(trans->getDuration(), ccScene);
				break;
			case transition_pageTurn:
				ccScene = cocos2d::CCTransitionPageTurn::create(trans->getDuration(), ccScene, false);
				break;
			case transition_progressHorizontal:
				ccScene = cocos2d::CCTransitionProgressHorizontal::create(trans->getDuration(), ccScene);
				break;
			case transition_progressInOut:
				ccScene = cocos2d::CCTransitionProgressInOut::create(trans->getDuration(), ccScene);
				break;
			case transition_progressOutIn:
				ccScene = cocos2d::CCTransitionProgressOutIn::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCCW:
				ccScene = cocos2d::CCTransitionProgressRadialCCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCW:
				ccScene = cocos2d::CCTransitionProgressRadialCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressVertical:
				ccScene = cocos2d::CCTransitionProgressVertical::create(trans->getDuration(), ccScene);
				break;
			case transition_rotoZoom:
				ccScene = cocos2d::CCTransitionRotoZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_shrinkGrow:
				ccScene = cocos2d::CCTransitionShrinkGrow::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInB:
				ccScene = cocos2d::CCTransitionSlideInB::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInL:
				ccScene = cocos2d::CCTransitionSlideInL::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInR:
				ccScene = cocos2d::CCTransitionSlideInR::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInT:
				ccScene = cocos2d::CCTransitionSlideInT::create(trans->getDuration(), ccScene);
				break;
			case transition_splitCols:
				ccScene = cocos2d::CCTransitionSplitCols::create(trans->getDuration(), ccScene);
				break;
			case transition_splitRows:
				ccScene = cocos2d::CCTransitionSplitRows::create(trans->getDuration(), ccScene);
				break;
			case transition_turnOffTiles:
				ccScene = cocos2d::CCTransitionTurnOffTiles::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipAngular:
				ccScene = cocos2d::CCTransitionZoomFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipX:
				ccScene = cocos2d::CCTransitionZoomFlipX ::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipY:
				ccScene = cocos2d::CCTransitionZoomFlipY::create(trans->getDuration(), ccScene);
				break;
			case transition_none:
			default:
				//use no transition
				break;
		}
	}
	
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	if(pDirector->getRunningScene())
	{
		//either push this scene or replace the current one on top of the stack
		if(push)
			pDirector->pushScene(ccScene);
		else
			pDirector->replaceScene(ccScene);
	}
	else
	{
		//This is our first scene, which requires a different API
		pDirector->runWithScene(ccScene);
	}
	
	return true;
}
