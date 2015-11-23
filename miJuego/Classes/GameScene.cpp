#include "GameScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"


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


/*void GameScene::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void GameScene::goToGameOverScene(Ref *pSender) {
	auto scene = GameOverScene::createScene();

	Director::getInstance()->replaceScene(scene);
}
*/


bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto background = Sprite::create("background.jpg");

	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));

	addChild(background, 0);

	prota = new Prota();
	prota->posicion = Vec2(0, (visibleSize.height / 2));
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);


	_pressedKey = EventKeyboard::KeyCode::KEY_NONE;

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	


	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	_pressedKey = keyCode;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (prota->getOrientacion() != 'w' && prota->getOrientacion() != 'e') {
			prota->setOrientacion('w');
			removeChild(prota->sprite);
			prota->cambiarSprite();
			addChild(prota->sprite);
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w') {
			prota->setOrientacion('e');
			removeChild(prota->sprite);
			prota->cambiarSprite();
			addChild(prota->sprite);
		}
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's') {
			prota->setOrientacion('n');
			removeChild(prota->sprite);
			prota->cambiarSprite();
			addChild(prota->sprite);
		}
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n') {
			prota->setOrientacion('s');
			removeChild(prota->sprite);
			prota->cambiarSprite();
			addChild(prota->sprite);

		}
		break;

	}


}
void GameScene::update(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (prota->getOrientacion() == 'e') {
		prota->posicion = Vec2(prota->posicion.x + 5, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);

	}

	else if (prota->getOrientacion() == 'w') {
		prota->posicion = Vec2(prota->posicion.x - 5, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);


	}

	else if (prota->getOrientacion() == 'n') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 5);
		prota->sprite->setPosition(prota->posicion);

	}

	else if (prota->getOrientacion() == 's') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 5);
		prota->sprite->setPosition(prota->posicion);
	}



}