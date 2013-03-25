#include "CocosAppDelegate.h"
#include <libxml/parser.h>
#include "Director.h"
#include "SceneReference.h"
#include "Scene.h"
#include "Transition.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "Cocos2dXMLTouchDelegate.h"

USING_NS_CC;

#pragma mark - application lifecycle

bool CocosAppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setOpenGLView(pEGLView);
	
	//init our custom Cocos2dXML touch handling
	Cocos2dXMLTouchDelegate::initDelegate();
	
	//load the XML file that will drive the director
	const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("main.xml");
	xmlDocPtr xmlDocument = xmlReadFile(fullPath, NULL, XML_PARSE_XINCLUDE|XML_PARSE_NONET|XML_PARSE_NSCLEAN);
	if(!xmlDocument)
	{
		//TODO: bad XML file
		return false;
	}
	Director* xmlDirector = new Director();
	xmlDirector->initWithXML(xmlDocument->children, NULL);
	xmlDirector->load();
	
	return true;
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
