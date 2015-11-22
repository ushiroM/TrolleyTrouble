#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Prota.h"

class GameScene: public cocos2d::Layer
{
private:
	Prota* prota;
	EventKeyboard::KeyCode _pressedKey;
	
public:
	static cocos2d::Scene* createScene();
	//void goToPauseScene(Ref *pSender);
	//void goToGameOverScene(Ref *pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void update(float dt);
	virtual bool init();
	//bool isKeyPressed(EventKeyboard::KeyCode code);

	CREATE_FUNC(GameScene);

};

#endif

