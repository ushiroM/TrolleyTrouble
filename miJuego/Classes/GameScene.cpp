#include "GameScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "Enemigo.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);

	scene->getPhysicsWorld()->setAutoStep(false);		 
	scene->getPhysicsWorld()->step(0.001f);
	scene->getPhysicsWorld()->setAutoStep(true);

	// return the scene
	return scene;
}

void GameScene::setPhysicsWorld(PhysicsWorld *world) {
	mWorld = world;
	mWorld->setGravity(Vec2::ZERO);
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


	//auto background = Sprite::create("background.jpg");

	//background->setPosition(Point((visibleSize.width / 2),
		//(visibleSize.height / 2)));

	//addChild(background, 0);

	prota = new Prota();
	auto body = PhysicsBody::createCircle(prota->sprite->getBoundingBox().size.width / 2);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	prota->sprite->setPhysicsBody(body);
	prota->posicion = Vec2(0, (visibleSize.height / 2));
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);

	Enemigo* enemigo = new Enemigo();
	auto bodyenemigo = PhysicsBody::createCircle(enemigo->sprite->getBoundingBox().size.width / 2);
	bodyenemigo->setContactTestBitmask(true);
	//bodyenemigo->setDynamic(true);
	enemigo->sprite->setPhysicsBody(bodyenemigo);
	enemigo->sprite->setPosition(Vec2(1000, 500));
	addChild(enemigo->sprite);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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

bool GameScene::onContactBegin(PhysicsContact &contact) {

	if (prota->getOrientacion() == 'e') {
		prota->setOrientacion('w');
		
	}

	else if (prota->getOrientacion() == 'w') {
		prota->setOrientacion('e');

	}

	else if (prota->getOrientacion() == 'n') {
		prota->setOrientacion('s');
	}

	else if (prota->getOrientacion() == 's') {
		prota->setOrientacion('n');
	}

	removeChild(prota->sprite);
	prota->cambiarSprite();
	addChild(prota->sprite);

	return true;
}