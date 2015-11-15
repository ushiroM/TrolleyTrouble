#include "GameScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "Prota.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


void GameScene::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void GameScene::goToGameOverScene(Ref *pSender) {
	auto scene = GameOverScene::createScene();

	Director::getInstance()->replaceScene(scene);
}

auto prota = Prota::create();

bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	prota->setPosition(Vec2(0, 0));
	addChild(prota);


	
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
	
	Vec2 loc = event->getCurrentTarget()->getPosition();
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if(prota->getOrientacion() != 'w' && prota->getOrientacion() != 'e')
				prota->setOrientacion('w');
			break;
		case EventKeyboard::KeyCode::KEY_A:
			event->getCurrentTarget()->setPosition(--loc.x, loc.y); // cambiar orientacion(todavia sin hacer)
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w')
				prota->setOrientacion('e');
			break;
		case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(++loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's')
				prota->setOrientacion('n');
			break;
		
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n')
				prota->setOrientacion('s');
			break;
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, --loc.y);
			break;
		/*case EventKeyboard::KeyCode::KEY_SPACE:
			prota->embestir();
			break;*/
	}
};

	
	


	return true;
}
