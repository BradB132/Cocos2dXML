#include "CocosAppDelegate.h"
#include <libxml/parser.h>
#include "Director.h"
#include "SceneReference.h"
#include "Scene.h"
#include "Transition.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "Cocos2dXMLTouchDelegate.h"

USING_NS_CC;

CocosAppDelegate::CocosAppDelegate():
xmlDirector(NULL),
currentScene(NULL)
{
}

CocosAppDelegate::~CocosAppDelegate()
{
	if(currentScene)
	{
		delete currentScene;
		currentScene = NULL;
	}
	if(xmlDirector)
	{
		delete xmlDirector;
		xmlDirector = NULL;
	}
}

#pragma mark - application lifecycle

bool CocosAppDelegate::applicationDidFinishLaunching()
{
	//load the XML file that will drive the director
	const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("main.xml");
	xmlDocPtr xmlDocument = xmlReadFile(fullPath, NULL, XML_PARSE_XINCLUDE|XML_PARSE_NONET|XML_PARSE_NSCLEAN);
	if(!xmlDocument)
	{
		//TODO: bad XML file
		return false;
	}
	xmlDirector = new Director();
	xmlDirector->initWithXML(xmlDocument->children, NULL);
	
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	
	pDirector->setOpenGLView(pEGLView);
	
	//set the content scale
	float smallerDesigned = (xmlDirector->getDesignedSize().x < xmlDirector->getDesignedSize().y) ? xmlDirector->getDesignedSize().x : xmlDirector->getDesignedSize().y;
	float smallerScreenSize = (pEGLView->getFrameSize().width < pEGLView->getFrameSize().height) ? pEGLView->getFrameSize().width : pEGLView->getFrameSize().height;
	int scaleFactor = (int)(smallerScreenSize/smallerDesigned);
	CCSize frame = pEGLView->getFrameSize();
	pEGLView->setDesignResolutionSize(frame.width/scaleFactor, frame.height/scaleFactor, kResolutionNoBorder);
	pDirector->setContentScaleFactor(scaleFactor);
	
	// set attributes of the director based on XML arguments
	pDirector->setDisplayStats(xmlDirector->getDisplayStats());
	pDirector->setAnimationInterval(1.0/xmlDirector->getFps());
	pDirector->setBackgroundColor(xmlDirector->getColor());
	
	Cocos2dXMLTouchDelegate::initDelegate();
	
	if(xmlDirector->getSceneReferences()->count() > 0)
	{
		//default to the first scene
		SceneReference* defaultScene = (SceneReference*)xmlDirector->getSceneReferences()->objectAtIndex(0);
		return switchToScene(defaultScene, NULL, false);
	}
	else
	{
		//TODO: how to handle case where we didn't specify any scenes?
		return false;
	}
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void CocosAppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void CocosAppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

#pragma mark - scene management

bool CocosAppDelegate::switchToScene(SceneReference* ref, Transition* trans, bool push)
{
	//load the xml
	const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(ref->getPath().c_str());
	xmlDocPtr xmlDocument = xmlReadFile(fullPath, NULL, XML_PARSE_XINCLUDE|XML_PARSE_NONET|XML_PARSE_NSCLEAN);
	if(!xmlDocument)
	{
		//TODO: bad XML file
		return false;
	}
	
	//create the new scene using the XML
	//TODO: figure out how to handle this with transitions, right now this is a massive leak!
//	if(currentScene)
//	{
//		delete currentScene;
//	}
	currentScene = new Scene();
	currentScene->initWithXML(xmlDocument->children, NULL);
	currentScene->visitLoad();
	CCScene* ccScene = dynamic_cast<CCScene*>(currentScene->getCCNode());
	if(!ccScene)
		return false;
	
	//wrap this scene in a transition
	if(trans)
	{
		switch(trans->getType())
		{
			case transition_crossFade:
				ccScene = CCTransitionCrossFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fade:
				ccScene = CCTransitionFade::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeBL:
				ccScene = CCTransitionFadeBL::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeDown:
				ccScene = CCTransitionFadeDown::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeTR:
				ccScene = CCTransitionFadeTR::create(trans->getDuration(), ccScene);
				break;
			case transition_fadeUp:
				ccScene = CCTransitionFadeUp::create(trans->getDuration(), ccScene);
				break;
			case transition_flipAngular:
				ccScene = CCTransitionFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_flipX:
				ccScene = CCTransitionFlipX::create(trans->getDuration(), ccScene);
				break;
			case transition_flipY:
				ccScene = CCTransitionFlipY::create(trans->getDuration(), ccScene);
				break;
			case transition_jumpZoom:
				ccScene = CCTransitionJumpZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInB:
				ccScene = CCTransitionMoveInB::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInL:
				ccScene = CCTransitionMoveInL::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInR:
				ccScene = CCTransitionMoveInR::create(trans->getDuration(), ccScene);
				break;
			case transition_moveInT:
				ccScene = CCTransitionMoveInT::create(trans->getDuration(), ccScene);
				break;
			case transition_pageTurn:
				ccScene = CCTransitionPageTurn::create(trans->getDuration(), ccScene, false);
				break;
			case transition_progressHorizontal:
				ccScene = CCTransitionProgressHorizontal::create(trans->getDuration(), ccScene);
				break;
			case transition_progressInOut:
				ccScene = CCTransitionProgressInOut::create(trans->getDuration(), ccScene);
				break;
			case transition_progressOutIn:
				ccScene = CCTransitionProgressOutIn::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCCW:
				ccScene = CCTransitionProgressRadialCCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressRadialCW:
				ccScene = CCTransitionProgressRadialCW::create(trans->getDuration(), ccScene);
				break;
			case transition_progressVertical:
				ccScene = CCTransitionProgressVertical::create(trans->getDuration(), ccScene);
				break;
			case transition_rotoZoom:
				ccScene = CCTransitionRotoZoom::create(trans->getDuration(), ccScene);
				break;
			case transition_shrinkGrow:
				ccScene = CCTransitionShrinkGrow::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInB:
				ccScene = CCTransitionSlideInB::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInL:
				ccScene = CCTransitionSlideInL::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInR:
				ccScene = CCTransitionSlideInR::create(trans->getDuration(), ccScene);
				break;
			case transition_slideInT:
				ccScene = CCTransitionSlideInT::create(trans->getDuration(), ccScene);
				break;
			case transition_splitCols:
				ccScene = CCTransitionSplitCols::create(trans->getDuration(), ccScene);
				break;
			case transition_splitRows:
				ccScene = CCTransitionSplitRows::create(trans->getDuration(), ccScene);
				break;
			case transition_turnOffTiles:
				ccScene = CCTransitionTurnOffTiles::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipAngular:
				ccScene = CCTransitionZoomFlipAngular::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipX:
				ccScene = CCTransitionZoomFlipX ::create(trans->getDuration(), ccScene);
				break;
			case transition_zoomFlipY:
				ccScene = CCTransitionZoomFlipY::create(trans->getDuration(), ccScene);
				break;
			case transition_none:
			default:
				//use no transition
				break;
		}
	}
	
	CCDirector* pDirector = CCDirector::sharedDirector();
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
