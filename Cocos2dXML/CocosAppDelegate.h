#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "Cocos2dXML_enums.h"

class Director;
class SceneReference;
class Transition;
class Scene;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  CocosAppDelegate : private cocos2d::CCApplication
{
public:
    CocosAppDelegate();
    virtual ~CocosAppDelegate();

	//application lifecycle
    virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
	
	//scene management
	virtual bool switchToScene(SceneReference* ref, Transition* trans, bool push);
	
protected:
	
	Director* xmlDirector;
	Scene* currentScene;
};

#endif // _APP_DELEGATE_H_

