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
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

void GameScene::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void GameScene::goToGameOverScene(Ref *pSender) {
	auto escenaGameOver = GameOverScene::createScene();
	Director::getInstance()->replaceScene(escenaGameOver);
}

bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	crearSala();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	prota = new Prota();
	auto body = PhysicsBody::createBox(prota->sprite->getBoundingBox().size);
	prota->sprite->setTag(5);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	prota->sprite->setPhysicsBody(body);
	//auto spritePos = Vec3(visibleSize.width / 2, visibleSize.height / 2, 0);
	prota->posicion = Vec2(200, visibleSize.height /2);
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);

	Enemigo* enemigo5 = new Enemigo();
	enemigo5->sprite = Sprite::create("enemijo.png");
	enemigo5->sprite->setTag(10);
	auto bodyenemigo5 = PhysicsBody::createBox(enemigo5->sprite->getBoundingBox().size);
	bodyenemigo5->setContactTestBitmask(true);
	bodyenemigo5->setDynamic(false);
	enemigo5->sprite->setPhysicsBody(bodyenemigo5);
	enemigo5->sprite->setPosition(Vec2(700,500));
	addChild(enemigo5->sprite);

	barraEnergia->setPosition(Vec2(0, 660));
	addChild(barraEnergia);

	energyLabel->setPosition(Vec2(270, 660));
	addChild(energyLabel);

	lifeLabel->setPosition(Vec2(270, 700));
	addChild(lifeLabel);

	barraVida->setPosition(Vec2(0, 700));
	addChild(barraVida);


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
		if (placando == false && prota->energia >= 70) {
			prota->energia = prota->energia - 70;
			placando = true;
			velocidadanterior = prota->velocidad;
			prota->velocidad = 2;
			if (prota->getOrientacion() == 'e') prota->sprite->setTexture("emfestirDerecho.png");
			else if (prota->getOrientacion() == 'w') prota->sprite->setTexture("emfestirIzquierdo.png");
			this->schedule(schedule_selector(GameScene::frenar), 0.3f);
		}
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		goToPauseScene(this);
		break;

	}
}

void GameScene::frenar(float dt) {
	this->unschedule(schedule_selector(GameScene::frenar));
	prota->velocidad = velocidadanterior;
	prota->cambiarSprite();
	placando = false;
}

void GameScene::rotarProta() {

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
}

void GameScene::crearSala() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	// create a TMX map
	auto layer = map->getLayer("piso");
	map->setPosition(Vec2(0, -2880));
	addChild(map, 0, 1);
	
	Size s = layer->getLayerSize();
	for (int x = 0; x < s.width; x++){
		for (int y = 0; y < s.height; y++){
			int tileGID = layer->getTileGIDAt(Vec2(x, y));
			if (tileGID != 4 && tileGID != 8){
				addColision(layer->getTileAt(Vec2(x, y)), tileGID);
			}
		}
	}
	//map->setPosition(Vec2(0, -2880));
}

void GameScene::addColision(Sprite * sprite, int tipo)
{
	auto bodye = PhysicsBody::createBox(sprite->getBoundingBox().size);
	bodye->setContactTestBitmask(true);
	bodye->setDynamic(false);
	sprite->setTag(tipo);
	sprite->setPhysicsBody(bodye);
}

void GameScene::update(float dt) {

	if (cruzarPuerta == true) {
		cruzarPuerta = false;
		centerViewport(scrollX, scrollY);
	}

	a = true;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	barraEnergia->setScaleX(prota->energia*4);
	if (prota->energia < 100) prota->energia++;

	barraVida->setScaleX(prota->vida * 4);
	
	if (prota->getOrientacion() == 'e') {
		prota->posicion = Vec2(prota->posicion.x + 5 * prota->velocidad, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);
	}

	else if (prota->getOrientacion() == 'w') {
		prota->posicion = Vec2(prota->posicion.x - 5*prota->velocidad, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);
	}

	else if (prota->getOrientacion() == 'n') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 5*prota->velocidad);
		prota->sprite->setPosition(prota->posicion);

	}

	else if (prota->getOrientacion() == 's') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 5*prota->velocidad);
		prota->sprite->setPosition(prota->posicion);
	}

	if (prota->vida <= 0) goToGameOverScene(this); //HUAAAAAAAAAAOOOO
}


void GameScene::centerViewport(float scrollX, float scrollY) {
	
	float x = this->getPositionX();
	float y = this->getPositionY();
	
	/*barraEnergia->setPosition(Vec2(barraEnergia->getPositionX() + scrollX, barraEnergia->getPositionY() + scrollY));
	barraVida->setPosition(Vec2(barraVida->getPositionX() + scrollX, barraVida->getPositionY() + scrollY));
	energyLabel->setPosition(Vec2(energyLabel->getPositionX() + scrollX, energyLabel->getPositionY() + scrollY));
	lifeLabel->setPosition(Vec2(lifeLabel->getPositionX() + scrollX, lifeLabel->getPositionY() + scrollY));*/
	this->setPosition(Vec2(x+scrollX, y+scrollY));
}

bool GameScene::onContactBegin(PhysicsContact &contact) {

	float x = map->getPositionX();
	float y = map->getPositionY();
	if (b) {
		b = false;
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();

		if (nodeA && nodeB)
		{
			if (nodeA->getTag() == 5) {
				switch (nodeB->getTag())
				{
				case 10:
					if (placando == true) {
						removeChild(nodeB, true);
						frenar(0.0);
					}
					else {
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 2:
					if (a) {
						a = false;
						frenar(0.0);
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 1:
					prota->posicion = Vec2(prota->posicion.x + 218, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = -1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 5:
					prota->posicion = Vec2(prota->posicion.x - 218, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 3:
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 160);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = 720;
					cruzarPuerta = true;
					break;
				case 6:
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 160);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = -720;
					cruzarPuerta = true;
					break;
				default:
					break;
				}
			}
			else if (nodeB->getTag() == 5) {
				switch (nodeA->getTag())
				{
				case 10:
					if (placando == true) {
						removeChild(nodeA, true);
						frenar(0.0);
					}
					else {
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 2:
					if (a) {
						a = false;
						frenar(0.0);
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 1:
					prota->posicion = Vec2(prota->posicion.x + 218, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = -1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 5:
					prota->posicion = Vec2(prota->posicion.x - 218, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 3:
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 160);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = 720;
					cruzarPuerta = true;
					break;
				case 6:
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 160);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = -720;
					cruzarPuerta = true;
					break;
				default:
					break;
				}
			}
		}
	}
	b = true;
	return true;
}