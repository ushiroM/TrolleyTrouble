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
	scene->getPhysicsWorld()->step(1.0f);
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
	auto body = PhysicsBody::createBox(prota->sprite->getBoundingBox().size);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	prota->sprite->setPhysicsBody(body);
	prota->posicion = Vec2(200, (visibleSize.height / 2));
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);

	
	Enemigo* enemigo = new Enemigo();
	auto bodyenemigo = PhysicsBody::createBox(enemigo->sprite->getBoundingBox().size);
	bodyenemigo->setContactTestBitmask(true);
	bodyenemigo->setDynamic(false);
	enemigo->sprite->setPhysicsBody(bodyenemigo);
	enemigo->sprite->setPosition(Vec2(35, (visibleSize.height) / 2));
	addChild(enemigo->sprite);

	Enemigo* enemigo2 = new Enemigo();
	auto bodyenemigo2 = PhysicsBody::createBox(enemigo2->sprite->getBoundingBox().size);
	bodyenemigo2->setContactTestBitmask(true);
	bodyenemigo2->setDynamic(false);
	enemigo2->sprite->setPhysicsBody(bodyenemigo2);
	enemigo2->sprite->setPosition(Vec2((visibleSize.width) - 35, (visibleSize.height)/2));
	addChild(enemigo2->sprite);

	Enemigo* enemigo3 = new Enemigo();
	enemigo3->sprite = Sprite::create("paredtest2.png");
	auto bodyenemigo3 = PhysicsBody::createBox(enemigo3->sprite->getBoundingBox().size);
	bodyenemigo3->setContactTestBitmask(true);
	bodyenemigo3->setDynamic(false);
	enemigo3->sprite->setPhysicsBody(bodyenemigo3);
	enemigo3->sprite->setPosition(Vec2((visibleSize.width)/2, (visibleSize.height) - 35));
	addChild(enemigo3->sprite);

	Enemigo* enemigo4 = new Enemigo();
	enemigo4->sprite = Sprite::create("paredtest2.png");
	auto bodyenemigo4 = PhysicsBody::createBox(enemigo4->sprite->getBoundingBox().size);
	bodyenemigo4->setContactTestBitmask(true);
	bodyenemigo4->setDynamic(false);
	enemigo4->sprite->setPhysicsBody(bodyenemigo4);
	enemigo4->sprite->setPosition(Vec2((visibleSize.width) / 2, 35));
	addChild(enemigo4->sprite);




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
			prota->cambiarSprite();
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w') {
			prota->setOrientacion('e');
			prota->cambiarSprite();
		}
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's') {
			prota->setOrientacion('n');
			prota->cambiarSprite();
		}
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n') {
			prota->setOrientacion('s');
			prota->cambiarSprite();

		}
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		velocidadanterior = prota->velocidad;
		prota->velocidad = 100;
		if (prota->getOrientacion() == 'e') prota->sprite->setTexture("embestirDerecho.png");
		else if (prota->getOrientacion() == 'w') prota->sprite->setTexture("embestirIzquierdo.png");
		this->schedule(schedule_selector(GameScene::frenar), 0.02f);
		break;

	}


}

void GameScene::frenar(float dt) {
	prota->velocidad = velocidadanterior;
	prota->cambiarSprite();
}


void GameScene::update(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (prota->getOrientacion() == 'e') {
		prota->posicion = Vec2(prota->posicion.x + prota->velocidad, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);

	}

	else if (prota->getOrientacion() == 'w') {
		prota->posicion = Vec2(prota->posicion.x - prota->velocidad, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);


	}

	else if (prota->getOrientacion() == 'n') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + prota->velocidad);
		prota->sprite->setPosition(prota->posicion);

	}

	else if (prota->getOrientacion() == 's') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - prota->velocidad);
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

	prota->cambiarSprite();

	return true;
}