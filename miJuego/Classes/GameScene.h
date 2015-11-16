#pragma once
#include "cocos2d.h"
#include <map>
#include "Prota.h"

class GameScene: public cocos2d::Layer
{
	Prota* prota;
	Sprite* imagenProta;
	
public:
	static cocos2d::Scene* createScene();
	void goToPauseScene(Ref *pSender);
	void goToGameOverScene(Ref *pSender);
	virtual bool init();
	//void update();
	//bool isKeyPressed(EventKeyboard::KeyCode code);

};

