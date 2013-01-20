#include "CocosAppDelegate.h"
#include "Cocos2dXMLScene.h"

USING_NS_CC;

CocosAppDelegate::CocosAppDelegate() {

}

CocosAppDelegate::~CocosAppDelegate()
{
}

bool CocosAppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

#ifdef COCOS2D_DEBUG
	
	// turn on display FPS
	pDirector->setDisplayStats(true);
	
	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

#endif
	
	// create a scene. it's an autorelease object
	Cocos2dXMLScene *pScene = Cocos2dXMLScene::scene(NULL);

	// run
	pDirector->runWithScene(pScene);

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
