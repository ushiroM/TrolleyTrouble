#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	void GoToGameScene(Ref *pSender);

    virtual bool init();
    
    // a selector callback
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __HELLOWORLD_SCENE_H__
