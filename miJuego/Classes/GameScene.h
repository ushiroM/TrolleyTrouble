#pragma once
#include "cocos2d.h"
#include <map>

class GameScene: public cocos2d::Layer
{

	
public:
	static cocos2d::Scene* createScene();
	void goToPauseScene(Ref *pSender);
	void goToGameOverScene(Ref *pSender);
	virtual bool init();
	void update();
	bool isKeyPressed(EventKeyboard::KeyCode code);

};

