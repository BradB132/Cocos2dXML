#ifndef __Cocos2dXMLScene_H__
#define __Cocos2dXMLScene_H__

#include "cocos2d.h"

class Cocos2dXMLScene : public cocos2d::CCScene
{
public:

    virtual bool initWithXMLPath(char* xmlPath);

    static Cocos2dXMLScene* scene(char* xmlPath);
    
    CREATE_FUNC(Cocos2dXMLScene);
};

#endif // __Cocos2dXMLScene_SCENE_H__
