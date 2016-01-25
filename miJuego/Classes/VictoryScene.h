#pragma once
#include "cocos2d.h"

class VictoryScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	void goToMainMenu(Ref *pSender);
	virtual bool init();

	CREATE_FUNC(VictoryScene);
};