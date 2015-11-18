#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Prota.h"

class MainMenuScene : public cocos2d::Layer
{
private:

	Prota* prota;
	EventKeyboard::KeyCode _pressedKey;

public:
    static cocos2d::Scene* createScene();

	void GoToGameScene(Ref *pSender);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);

	void update(float dt);

    virtual bool init();
    
    // a selector callback
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __HELLOWORLD_SCENE_H__
