#pragma once
#include "cocos2d.h"



class PauseScene: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	void resumeGameScene(Ref *pSender);
	void goToMainMenu(Ref *pSender);
	void retryGameScene(Ref *pSender);

};

