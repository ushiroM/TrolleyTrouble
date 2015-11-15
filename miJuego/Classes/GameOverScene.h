#pragma once

#include "cocos2d.h"


class GameOverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	void goToMainMenu(Ref *pSender);
	void retryGameScene(Ref *pSender);


};

