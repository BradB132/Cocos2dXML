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
	
	//create an empty scene arrays
	sceneStack = cocos2d::CCArray::create();
	discardedScenes = cocos2d::CCArray::create();
	sceneStack->retain();
	discardedScenes->retain();
	
	//set attributes of the director based on XML arguments
	refreshAllAttributes();
	
	if(SceneReferences->count() > 0)
	{
		//default to the first scene
		SceneReference* defaultScene = (SceneReference*)SceneReferences->objectAtIndex(0);
		switchToScene(defaultScene, NULL, false);
	}
	
	//we want to be able to check discarded scenes frequently, use the update loop
	cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
	
	Director_Base::load();
}

void Director::unload()
{
	//remove self from scheduler
	cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
	
	Director_Base::unload();
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
			
			//the call to setDesignResolutionSize sets the director back to defaults for several states, change them back to what we want here
			attributeDidChange(id_Director_color);
			attributeDidChange(id_Director_depthTest);
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
	
	//create the new scene using the XML
	Scene* newScene = new Scene();
	newScene->autorelease();
	newScene->initWithXML(xmlDocument->children, NULL);
	newScene->visitLoad();
	cocos2d::CCScene* ccScene = dynamic_cast<cocos2d::CCScene*>(newScene->getCCNode());
	if(!ccScene)
	{
		newScene->visitLoad();
		return false;
	}
	
	//wrap this scene in a transition?
	cocos2d::CCScene* transitionScene = ccScene;
	if(trans)
	{
		switch(trans->getType())
		{
			case transition_crossFade:
				transitionScene = cocos2d::CCTransitionCrossFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fade:
				transitionScene = cocos2d::CCTransitionFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeBL:
				transitionScene = cocos2d::CCTransitionFadeBL::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeDown:
				transitionScene = cocos2d::CCTransitionFadeDown::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeTR:
				transitionScene = cocos2d::CCTransitionFadeTR::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeUp:
				transitionScene = cocos2d::CCTransitionFadeUp::create(trans->getDuration(), ccScene);
				break;
			case transition_flipAngular:
				transitionScene = cocos2d::CCTransitionFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_flipX:
				transitionScene = cocos2d::CCTransitionFlipX::create(trans->getDuration(), ccScene);
				break;
			case transition_flipY:
				transitionScene = cocos2d::CCTransitionFlipY::create(trans->getDuration(), ccScene);
				break;
			case transition_jumpZoom:
				transitionScene = cocos2d::CCTransitionJumpZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInB:
				transitionScene = cocos2d::CCTransitionMoveInB::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInL:
				transitionScene = cocos2d::CCTransitionMoveInL::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInR:
				transitionScene = cocos2d::CCTransitionMoveInR::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInT:
				transitionScene = cocos2d::CCTransitionMoveInT::create(trans->getDuration(), ccScene);
				break;
			case transition_pageTurn:
				transitionScene = cocos2d::CCTransitionPageTurn::create(trans->getDuration(), ccScene, false);
				break;
			case transition_progressHorizontal:
				transitionScene = cocos2d::CCTransitionProgressHorizontal::create(trans->getDuration(), ccScene);
				break;
			case transition_progressInOut:
				transitionScene = cocos2d::CCTransitionProgressInOut::create(trans->getDuration(), ccScene);
				break;
			case transition_progressOutIn:
				transitionScene = cocos2d::CCTransitionProgressOutIn::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCCW:
				transitionScene = cocos2d::CCTransitionProgressRadialCCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCW:
				transitionScene = cocos2d::CCTransitionProgressRadialCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressVertical:
				transitionScene = cocos2d::CCTransitionProgressVertical::create(trans->getDuration(), ccScene);
				break;
			case transition_rotoZoom:
				transitionScene = cocos2d::CCTransitionRotoZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_shrinkGrow:
				transitionScene = cocos2d::CCTransitionShrinkGrow::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInB:
				transitionScene = cocos2d::CCTransitionSlideInB::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInL:
				transitionScene = cocos2d::CCTransitionSlideInL::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInR:
				transitionScene = cocos2d::CCTransitionSlideInR::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInT:
				transitionScene = cocos2d::CCTransitionSlideInT::create(trans->getDuration(), ccScene);
				break;
			case transition_splitCols:
				transitionScene = cocos2d::CCTransitionSplitCols::create(trans->getDuration(), ccScene);
				break;
			case transition_splitRows:
				transitionScene = cocos2d::CCTransitionSplitRows::create(trans->getDuration(), ccScene);
				break;
			case transition_turnOffTiles:
				transitionScene = cocos2d::CCTransitionTurnOffTiles::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipAngular:
				transitionScene = cocos2d::CCTransitionZoomFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipX:
				transitionScene = cocos2d::CCTransitionZoomFlipX ::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipY:
				transitionScene = cocos2d::CCTransitionZoomFlipY::create(trans->getDuration(), ccScene);
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
		{
			sceneStack->addObject(newScene);
			pDirector->pushScene(transitionScene);
		}
		else
		{
			//substitute the new scene
			discardTopScene();
			sceneStack->addObject(newScene);
			
			pDirector->replaceScene(transitionScene);
		}
	}
	else
	{
		//This is our first scene, which requires a different API
		sceneStack->addObject(newScene);
		pDirector->runWithScene(ccScene);
	}
	
	return true;
}

void Director::popScene()
{
	discardTopScene();
	
	cocos2d::CCDirector::sharedDirector()->popScene();
}

void Director::popToRootScene()
{
	while(sceneStack->count() > 1)
		discardTopScene();
	
	cocos2d::CCDirector::sharedDirector()->popToRootScene();
}

void Director::discardTopScene()
{
	Scene* removedScene = (Scene*)sceneStack->lastObject();
	discardedScenes->addObject(removedScene);
	sceneStack->removeLastObject();
}

void Director::update(float dt)
{
	//check the discarded scenes to see if they're done transitioning
	cocos2d::ccArray* arr = discardedScenes->data;
	for(int i = arr->num-1; i >= 0; i--)
	{
		Scene* scene = (Scene*)arr->arr[i];
		cocos2d::CCScene* ccScene = (cocos2d::CCScene*)(scene->getCCNode());
		if(!ccScene->isTransitioning())
		{
			scene->visitUnload();
			discardedScenes->removeObjectAtIndex(i);
		}
	}
}
