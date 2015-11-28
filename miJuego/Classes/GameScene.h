#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Prota.h"

class GameScene: public cocos2d::Layer
{
private:
	Prota* prota;
	EventKeyboard::KeyCode _pressedKey;
	PhysicsWorld *mWorld;
	PhysicsBody *body;

	
public:
	static cocos2d::Scene* createScene();
	//void goToPauseScene(Ref *pSender);
	//void goToGameOverScene(Ref *pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void update(float dt);
	virtual bool init();
	//bool isKeyPressed(EventKeyboard::KeyCode code);
	void setPhysicsWorld(PhysicsWorld *world);
	bool onContactBegin(PhysicsContact &contact);

	CREATE_FUNC(GameScene);

};

#endif

