#include "Cocos2dXMLScene.h"

USING_NS_CC;

Cocos2dXMLScene* Cocos2dXMLScene::scene(char* xmlPath)
{
    Cocos2dXMLScene* pRet = new Cocos2dXMLScene();
    if (pRet && pRet->initWithXMLPath(xmlPath))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

// on "init" you need to initialize your instance
bool Cocos2dXMLScene::initWithXMLPath(char* xmlPath)
{
    bool superInit = cocos2d::CCScene::init();
	if(superInit)
	{
		//TODO: set up scene from XML
	}
    return superInit;
}
