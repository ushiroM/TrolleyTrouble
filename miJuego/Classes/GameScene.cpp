#include "GameScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#define COCOS2D_DEBUG 1


USING_NS_CC;


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //que se vean las colisiones de las cajas
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);
	scene->getPhysicsWorld()->setAutoStep(false);
	scene->getPhysicsWorld()->step(1.0f);
	scene->getPhysicsWorld()->setAutoStep(true); //esperar a que carguen las físicas

	// return the scene
	return scene;
}


void GameScene::setPhysicsWorld(PhysicsWorld *world) {
	mWorld = world;
	mWorld->setGravity(Vec2::ZERO);
}

void GameScene::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene); //meter la escena de pausa en la pila
}
void GameScene::goToGameOverScene(Ref *pSender) {
	auto escenaGameOver = GameOverScene::createScene();
	Director::getInstance()->replaceScene(escenaGameOver); //reemplazar la escena actual con game over en la pila
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
	crearEnemigos();

	Size visibleSize = Director::getInstance()->getVisibleSize();

			
	//crear el prota y aádirle su cuerpo de box2d
	prota = new Prota();
	Size protasize = Size(prota->sprite->getBoundingBox().size.width - 30, prota->sprite->getBoundingBox().size.height - 30);
	auto body = PhysicsBody::createBox(protasize);
	prota->sprite->setTag(5);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	body->setRotationEnable(false);
	prota->sprite->setPhysicsBody(body);
	prota->posicion = Vec2(218, 280);
	prota->sprite->setPosition(prota->posicion);
	prota->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	prota->sprite->getPhysicsBody()->setCollisionBitmask(0x01);
	addChild(prota->sprite);


	
	//crear el HUD
	barraEnergia->setPosition(Vec2(55, 660));
	barraEnergia->setAnchorPoint(Vec2(0.f, 0.5f));
	addChild(barraEnergia);

	barraVida->setPosition(Vec2(55, 670));
	barraVida->setAnchorPoint(Vec2(0.f, 0.5f));
	addChild(barraVida);

	hud->setPosition(Vec2(190, 670));
	addChild(hud);

	// Label Medidor [SE BORRARA]
	/*labelRobo = Label::create(std::to_string(girar), "Fonts/Arial.ttf", 20);
	labelRobo->setPosition(Point(prota->sprite->getPositionX() + 200, prota->sprite->getPositionY()));
	labelRobo->setColor(Color3B(0, 255, 0));
	addChild(labelRobo);*/

	//crear eventos para cuando 2 cajas de box2d empiezan a colisionar, y dejan de colisionar
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactEnd, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//crear un evento para cuando se pulsen teclas del teclado
	_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//crear la función update()
	this->scheduleUpdate();
	
	return true;
}

//evento que gestiona las teclas pulsadas
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	_pressedKey = keyCode;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (prota->getOrientacion() != 'w' && prota->getOrientacion() != 'e' && girar == true) {
			if (prota->getOrientacion() == 's') {
				prota->posicion = Vec2(posiCruce.x, posiCruce.y - 50);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posiCruce.x, posiCruce.y + 50);
				prota->sprite->setPosition(prota->posicion);
			}
			
			
			prota->setOrientacion('w');
			prota->cambiarSprite();
			
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w' && girar == true) {
			
			if (prota->getOrientacion() == 's') {
				prota->posicion = Vec2(posiCruce.x, posiCruce.y - 45);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posiCruce.x, posiCruce.y + 50);
				prota->sprite->setPosition(prota->posicion);
			}
			prota->setOrientacion('e');
			prota->cambiarSprite();
		}
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's' && girar == true) {
			if (prota->getOrientacion() == 'w') {
				prota->posicion = Vec2(posiCruce.x - 63, posiCruce.y);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posiCruce.x + 67, posiCruce.y);
				prota->sprite->setPosition(prota->posicion);
			}
			
			
			prota->setOrientacion('n');
			prota->cambiarSprite();
			
		}
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n' && girar == true) {
			if (prota->getOrientacion() == 'w') {
				prota->posicion = Vec2(posiCruce.x - 63, posiCruce.y);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posiCruce.x + 65, posiCruce.y);
				prota->sprite->setPosition(prota->posicion);
			}
			
			
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
			if (prota->getOrientacion() == 'e') prota->sprite->setTexture("prota/embestirDerecho.png");
			else if (prota->getOrientacion() == 'w') prota->sprite->setTexture("prota/embestirIzquierdo.png");
			this->schedule(schedule_selector(GameScene::frenar), 0.3f);
		}
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		goToPauseScene(this);
		break;

	case EventKeyboard::KeyCode::KEY_Z:
		if (tieneObjeto == true && cargaActual == 3) {
			velocidadenemiga = 2;
			cargaActual = 0;
		}
	}
}

//para que el prota vuelva a su velocidad previa al embestir
void GameScene::frenar(float dt) {
	this->unschedule(schedule_selector(GameScene::frenar));
	prota->velocidad = velocidadanterior;
	prota->cambiarSprite();
	placando = false;
}

//para dar la vuelta al prota al chocar contra paredes
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

void GameScene::rotarEnemigos(Enemigo* e) {
	if (e->getOrientacion() == 'e') {
		e->setOrientacion('w');
	}
	else if (e->getOrientacion() == 'w') {
		e->setOrientacion('e');
	}
	else if (e->getOrientacion() == 'n') {
		e->setOrientacion('s');
	}
	else if (e->getOrientacion() == 's') {
		e->setOrientacion('n');
	}
	e->cambiarSprite();
}
//crear el mapa
void GameScene::crearSala() {

	// create a TMX map
	auto layer = map->getLayer("piso");
	map->setPosition(Vec2(-218, -2480));
	addChild(map, 0, 1);
	
	//for que recorre el layer del mapaTMX
	Size s = layer->getLayerSize();
	for (int x = 0; x < s.width; x++){
		for (int y = 0; y < s.height; y++){
			int tileGID = layer->getTileGIDAt(Vec2(x, y)); //guardarse el GID del tile actual
			if (tileGID != 0 && tileGID != 1 && tileGID != 10 && tileGID != 19 && tileGID != 28 
				&& tileGID != 37 && tileGID != 46 && tileGID != 55 && tileGID != 64 && tileGID != 82 
				&& tileGID != 91 && tileGID != 100 && tileGID != 2 && tileGID != 11 && tileGID != 20 
				&& tileGID != 29 && tileGID != 38 && tileGID != 47 && tileGID != 56 && tileGID != 65 
				&& tileGID != 74 && tileGID != 83 && tileGID != 92 && tileGID != 101 && tileGID != 3 
				&& tileGID != 12 && tileGID != 21 && tileGID != 30 && tileGID != 39 && tileGID != 13 
				&& tileGID != 22 && tileGID != 33 && tileGID != 42 && tileGID != 51 && tileGID != 60 
				&& tileGID != 69 && tileGID != 78 && tileGID != 87){//si no es un tile de raíl recto, vacío, o de suelo
				if (tileGID != 48 && tileGID != 66 && tileGID != 68 && tileGID != 86 && tileGID != 57 && tileGID != 77 && tileGID != 24 && tileGID != 4) {
					addColision(layer->getTileAt(Vec2(x, y)), tileGID); //añadirle una caja de colisión al tile
				}
				else {
					int alrededor_l = layer->getTileGIDAt(Vec2(x - 1, y));
					int alrededor_r = layer->getTileGIDAt(Vec2(x + 1, y));
					int alrededor_u = layer->getTileGIDAt(Vec2(x ,y - 1));
					int alrededor_d = layer->getTileGIDAt(Vec2(x ,y + 1));
					if (alrededor_l != 5 && alrededor_l != 14 && alrededor_l != 23 && alrededor_l != 32 && alrededor_l != 41 && alrededor_l != 50 && alrededor_l != 59 && alrededor_l != 103 && alrededor_u != 5 && alrededor_u != 14 && alrededor_u != 23 && alrededor_u != 32 && alrededor_u != 41 && alrededor_u != 50 && alrededor_u != 59 && alrededor_u != 103 && alrededor_d != 5 && alrededor_d != 14 && alrededor_d != 23 && alrededor_d != 32 && alrededor_d != 41 && alrededor_d != 50 && alrededor_d != 59 && alrededor_d != 103 && alrededor_r != 5 && alrededor_r != 14 && alrededor_r != 23 && alrededor_r != 32 && alrededor_r != 41 && alrededor_r != 50 && alrededor_r != 59 && alrededor_r != 103) {
						addColision(layer->getTileAt(Vec2(x, y)), tileGID);
					}
					
				}
			}
		}
	}
	Objeto* reloj = new Objeto();
	reloj->sprite->setPosition(Vec2(1690, -1790));
	auto body = PhysicsBody::createBox(reloj->sprite->getBoundingBox().size);
	reloj->sprite->setTag(199);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	body->setRotationEnable(false);
	reloj->sprite->setPhysicsBody(body);
	reloj->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	reloj->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	addChild(reloj->sprite);

}

//función que añade cajas de colisión a los tiles, y un tag para las colisiones
void GameScene::addColision(Sprite * sprite, int tipo)
{
	PhysicsBody* bodye;
	switch (tipo){
	
	case 25: case 34: case 43: case 52: case 61: case 70: case 79: case 16: // si son curvas
		bodye = PhysicsBody::createBox(sprite->getBoundingBox().size / 2);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		bodye->setRotationEnable(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
		sprite->getPhysicsBody()->setCategoryBitmask(0x01);    
		sprite->getPhysicsBody()->setCollisionBitmask(0x01);   
		bodye->setRotationEnable(false);
		break;
		

	case 49: case 88:	//si el tile es un cruce de vías 
		bodye = PhysicsBody::createBox(sprite->getBoundingBox().size / 2);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		bodye->setRotationEnable(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
		sprite->getPhysicsBody()->setCategoryBitmask(0x01);
		sprite->getPhysicsBody()->setCollisionBitmask(0x01);
		break;

	default:	//cualquier otro tile
		bodye = PhysicsBody::createBox(sprite->getBoundingBox().size);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		bodye->setRotationEnable(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
		sprite->getPhysicsBody()->setCategoryBitmask(0x01);
		sprite->getPhysicsBody()->setCollisionBitmask(0x01);
		break;
	}
	
}

void GameScene::crearEnemigos() {

	Enemigo* enemigo1 = new Enemigo();
	enemigo1->sprite = Sprite::create("enemigos/cosa.png");
	enemigo1->sprite->setTag(201);
	enemigo1->tipo = 2;
	auto bodyenemigo1 = PhysicsBody::createBox(enemigo1->sprite->getBoundingBox().size/1.3);
	bodyenemigo1->setContactTestBitmask(true);
	bodyenemigo1->setDynamic(true);
	bodyenemigo1->setRotationEnable(false);
	enemigo1->sprite->setPhysicsBody(bodyenemigo1);
	enemigo1->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo1->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo1->sprite->setPosition(Vec2(1843, 275));
	enemigo1->setOrientacion('e');
	enemigo1->minX = 1618;
	enemigo1->maxX = 2500;
	addChild(enemigo1->sprite);
	enemigos.push_back(enemigo1);


	Enemigo* enemigo2 = new Enemigo();
	enemigo2->sprite = Sprite::create("enemigos/cosa.png");
	enemigo2->sprite->setTag(202);
	enemigo2->tipo = 2;
	auto bodyenemigo2 = PhysicsBody::createBox(enemigo2->sprite->getBoundingBox().size/1.3);
	bodyenemigo2->setContactTestBitmask(true);
	bodyenemigo2->setDynamic(true);
	bodyenemigo2->setRotationEnable(false);
	enemigo2->sprite->setPhysicsBody(bodyenemigo2);
	enemigo2->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo2->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo2->sprite->setPosition(Vec2(2208, -175));
	enemigo2->minX = 1671;
	enemigo2->maxX = 2446;
	addChild(enemigo2->sprite);
	enemigos.push_back(enemigo2);


	Enemigo* enemigo3 = new Enemigo();
	enemigo3->sprite = Sprite::create("enemigos/cosa.png");
	enemigo3->sprite->setTag(203);
	enemigo3->tipo = 1;
	auto bodyenemigo3 = PhysicsBody::createBox(enemigo3->sprite->getBoundingBox().size/1.3);
	bodyenemigo3->setContactTestBitmask(true);
	bodyenemigo3->setDynamic(true);
	bodyenemigo3->setRotationEnable(false);
	enemigo3->sprite->setPhysicsBody(bodyenemigo3);
	enemigo3->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo3->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo3->sprite->setPosition(Vec2(395, -340));
	enemigo3->minX = 373;
	enemigo3->maxX = 1103;
	addChild(enemigo3->sprite);
	enemigos.push_back(enemigo3);


	Enemigo* enemigo4 = new Enemigo();
	enemigo4->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo4->sprite->setTag(204);
	enemigo4->tipo = 1;
	auto bodyenemigo4 = PhysicsBody::createBox(enemigo4->sprite->getBoundingBox().size/1.3);
	bodyenemigo4->setContactTestBitmask(true);
	bodyenemigo4->setDynamic(true);
	bodyenemigo4->setRotationEnable(false);
	enemigo4->sprite->setPhysicsBody(bodyenemigo4);
	enemigo4->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo4->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo4->sprite->setPosition(Vec2(2015, -1235));
	enemigo4->minX = 1650;
	enemigo4->maxX = 2430;
	addChild(enemigo4->sprite);
	enemigos.push_back(enemigo4);
	
	
	Enemigo* enemigo5 = new Enemigo();
	enemigo5->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo5->sprite->setTag(205);
	enemigo5->tipo = 3;
	auto bodyenemigo5 = PhysicsBody::createBox(enemigo5->sprite->getBoundingBox().size/1.3);
	bodyenemigo5->setContactTestBitmask(true);
	bodyenemigo5->setDynamic(true);
	bodyenemigo5->setRotationEnable(false);
	enemigo5->sprite->setPhysicsBody(bodyenemigo5);
	enemigo5->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo5->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo5->setOrientacion('n');
	enemigo5->minY = -580;
	enemigo5->maxY = -270;
	enemigo5->sprite->setPosition(Vec2(2903, -385));
	addChild(enemigo5->sprite);
	enemigos.push_back(enemigo5);
	

	Enemigo* enemigo6 = new Enemigo();
	enemigo6->sprite = Sprite::create("enemigos/cosa.png");
	enemigo6->sprite->setTag(206);
	enemigo6->tipo = 2;
	auto bodyenemigo6 = PhysicsBody::createBox(enemigo6->sprite->getBoundingBox().size/1.3);
	bodyenemigo6->setContactTestBitmask(true);
	bodyenemigo6->setDynamic(true);
	bodyenemigo6->setRotationEnable(false);
	enemigo6->sprite->setPhysicsBody(bodyenemigo6);
	enemigo6->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo6->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo6->sprite->setPosition(Vec2(3408, 540));
	enemigo6->minX = 3045;
	enemigo6->maxX = 3560;
	addChild(enemigo6->sprite);
	enemigos.push_back(enemigo6);
	

	Enemigo* enemigo7 = new Enemigo();
	enemigo7->sprite = Sprite::create("enemigos/cosa.png");
	enemigo7->sprite->setTag(207);
	enemigo7->tipo = 2;
	auto bodyenemigo7 = PhysicsBody::createBox(enemigo7->sprite->getBoundingBox().size/1.3);
	bodyenemigo7->setContactTestBitmask(true);
	bodyenemigo7->setDynamic(true);
	bodyenemigo7->setRotationEnable(false);
	enemigo7->sprite->setPhysicsBody(bodyenemigo7);
	enemigo7->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo7->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo7->sprite->setPosition(Vec2(3495, -900));
	enemigo7->minX = 2788;
	enemigo7->maxX = 3738;
	addChild(enemigo7->sprite);
	enemigos.push_back(enemigo7);
	
	Enemigo* enemigo8 = new Enemigo();
	enemigo8->sprite = Sprite::create("enemigos/cosa.png");
	enemigo8->sprite->setTag(208);
	enemigo8->tipo = 2;
	auto bodyenemigo8 = PhysicsBody::createBox(enemigo8->sprite->getBoundingBox().size/1.3);
	bodyenemigo8->setContactTestBitmask(true);
	bodyenemigo8->setDynamic(true);
	bodyenemigo8->setRotationEnable(false);
	enemigo8->sprite->setPhysicsBody(bodyenemigo8);
	enemigo8->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo8->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo8->sprite->setPosition(Vec2(3718, -1230));
	enemigo8->minX = 2783;
	enemigo8->maxX = 3763;
	addChild(enemigo8->sprite);
	enemigos.push_back(enemigo8);
	
	Enemigo* enemigo9 = new Enemigo();
	enemigo9->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo9->sprite->setTag(209);
	enemigo9->tipo = 3;
	auto bodyenemigo9 = PhysicsBody::createBox(enemigo9->sprite->getBoundingBox().size/1.3);
	bodyenemigo9->setContactTestBitmask(true);
	bodyenemigo9->setDynamic(true);
	bodyenemigo9->setRotationEnable(false);
	enemigo9->sprite->setPhysicsBody(bodyenemigo9);
	enemigo9->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo9->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo9->sprite->setPosition(Vec2(1639, -123));
	enemigo9->minY = -555;
	enemigo9->maxY = -270;
	addChild(enemigo9->sprite);
	enemigos.push_back(enemigo9);
	
	Enemigo* enemigo10 = new Enemigo();
	enemigo10->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo10->sprite->setTag(210);
	enemigo10->tipo = 3;
	auto bodyenemigo10 = PhysicsBody::createBox(enemigo10->sprite->getBoundingBox().size/1.3);
	bodyenemigo10->setContactTestBitmask(true);
	bodyenemigo10->setDynamic(true);
	bodyenemigo10->setRotationEnable(false);
	enemigo10->sprite->setPhysicsBody(bodyenemigo10);
	enemigo10->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo10->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo10->sprite->setPosition(Vec2(2133, -860));
	enemigo9->minY = -1285;
	enemigo9->maxY = -865;
	addChild(enemigo10->sprite);
	enemigos.push_back(enemigo10);

	
	Enemigo* enemigo11 = new Enemigo();
	enemigo11->sprite = Sprite::create("enemigos/cosa.png");
	enemigo11->sprite->setTag(211);
	enemigo11->tipo = 2;
	auto bodyenemigo11 = PhysicsBody::createBox(enemigo11->sprite->getBoundingBox().size/1.3);
	bodyenemigo11->setContactTestBitmask(true);
	bodyenemigo11->setDynamic(true);
	bodyenemigo11->setRotationEnable(false);
	enemigo11->sprite->setPhysicsBody(bodyenemigo11);
	enemigo11->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo11->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo11->sprite->setPosition(Vec2(3341, 170));
	enemigo11->minX = 3039;
	enemigo11->maxX = 3391;
	addChild(enemigo11->sprite);
	enemigos.push_back(enemigo11);
	
	Enemigo* enemigo12 = new Enemigo();
	enemigo12->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo12->sprite->setTag(212);
	enemigo12->tipo = 3;
	auto bodyenemigo12 = PhysicsBody::createBox(enemigo12->sprite->getBoundingBox().size/1.3);
	bodyenemigo12->setContactTestBitmask(true);
	bodyenemigo12->setDynamic(true);
	bodyenemigo12->setRotationEnable(false);
	enemigo12->sprite->setPhysicsBody(bodyenemigo12);
	enemigo12->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo12->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo12->sprite->setPosition(Vec2(4800, -100));
	enemigo12->minY = -575;
	enemigo12->maxY = -110;
	addChild(enemigo12->sprite);
	enemigos.push_back(enemigo12);
	
	Enemigo* enemigo13 = new Enemigo();
	enemigo13->sprite = Sprite::create("enemigos/fantasma.png");
	enemigo13->sprite->setTag(213);
	enemigo13->tipo = 3;
	auto bodyenemigo13 = PhysicsBody::createBox(enemigo13->sprite->getBoundingBox().size /1.3);
	bodyenemigo13->setContactTestBitmask(true);
	bodyenemigo13->setDynamic(true);
	bodyenemigo13->setRotationEnable(false);
	enemigo13->sprite->setPhysicsBody(bodyenemigo13);
	enemigo13->sprite->getPhysicsBody()->setCategoryBitmask(0x03);
	enemigo13->sprite->getPhysicsBody()->setCollisionBitmask(0x02);
	enemigo13->sprite->setPosition(Vec2(2971, 605));
	enemigo13->minY = 140;
	enemigo13->maxY = 310;
	addChild(enemigo13->sprite);
	enemigos.push_back(enemigo13);
	

	
}
//función que se ejecuta periódicamente
void GameScene::update(float dt) {

	//labelRobo->setString("X: " + std::to_string(prota->sprite->getPositionX()) + ", Y: " + std::to_string(prota->sprite->getPositionY()) + ", ");

	//labelRobo->setPosition(Point(prota->sprite->getPositionX() + 200, prota->sprite->getPositionY()));

	a = true;

	for (int i = 0; i < enemigos.size(); i++) {
		if (enemigos[i] != nullptr) {
			enemigos[i]->movimiento(velocidadenemiga);
		}
	}
	
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//actualizar la barra de vida según la vida actual
	barraEnergia->setScaleX(prota->energia*3);
	if (prota->energia < 100) prota->energia++;
	barraVida->setScaleX(prota->vida*3);
	
	if (cruzarPuerta == false) {
		//mover al prota según la dirección que mira
		if (prota->getOrientacion() == 'e') {
			prota->posicion = Vec2(prota->posicion.x + 5 * prota->velocidad, prota->posicion.y);
			prota->sprite->setPosition(prota->posicion);
		}

		else if (prota->getOrientacion() == 'w') {
			prota->posicion = Vec2(prota->posicion.x - 5 * prota->velocidad, prota->posicion.y);
			prota->sprite->setPosition(prota->posicion);
		}

		else if (prota->getOrientacion() == 'n') {
			prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 5 * prota->velocidad);
			prota->sprite->setPosition(prota->posicion);

		}

		else if (prota->getOrientacion() == 's') {
			prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 5 * prota->velocidad);
			prota->sprite->setPosition(prota->posicion);
		}
	}

	if (cruzarPuerta == true) {
		centerViewport(scrollX, scrollY); //cambair la cámara al cruzar puertas
	}

	//si no queda vida, ir a la pantalla de game over
	if (prota->vida <= 0) goToGameOverScene(this); //HUAAAAAAAAAAOOOO
}

//función que centra la cámara en la sala actual
void GameScene::centerViewport(float scrollX, float scrollY) {
	
	float x = this->getPositionX();
	float y = this->getPositionY();
	hud->setPosition(Vec2(hud->getPositionX() - scrollX, hud->getPositionY() - scrollY));
	barraEnergia->setPosition(Vec2(barraEnergia->getPositionX() - scrollX, barraEnergia->getPositionY() - scrollY));
	barraVida->setPosition(Vec2(barraVida->getPositionX() - scrollX, barraVida->getPositionY() - scrollY));
	this->setPosition(Vec2(x+scrollX, y+scrollY));
}

//evento que se lanza cuando dos cuerpos de box2d dejan de colisionar


//evento que se lanza al empezar a colisionar dos cuerpos de box2d
bool GameScene::onContactBegin(PhysicsContact &contact) {

	if (contact.getShapeA()->getCategoryBitmask() == contact.getShapeB()->getCategoryBitmask() || contact.getShapeA()->getCollisionBitmask() == contact.getShapeB()->getCollisionBitmask()) {
		float x = map->getPositionX();
		float y = map->getPositionY();
		if (b) {
			b = false;
			auto nodeA = contact.getShapeA()->getBody()->getNode();
			auto nodeB = contact.getShapeB()->getBody()->getNode();

			if (nodeA && nodeB) //si ninguno es null
			{
				if (nodeA->getTag() == 5) { //si nodeA es el prota

					if (nodeB->getTag() > 200) { //cambiar
						if (placando == true) {
							for (int i = 0; i < enemigos.size(); i++) {
								if (enemigos[i] != nullptr) {
									if (enemigos[i]->sprite->getTag() == nodeB->getTag()) enemigos[i] = nullptr;
								}
							}
							removeChild(nodeB, true);	//eliminar al enemigo
							frenar(0.0);
						}
						else {
							prota->vida = prota->vida - 20;
							rotarProta();
						}
					}
					else {

						switch (nodeB->getTag())
						{
						case 4: case 6: case 7: case 15: case 24: case 48: case 57: case 66: case 68: case 73: case 75: case 77: case 84: case 86: case 93: case 95: case 96: case 102: case 104: case 105: case 31: case 40: case 58: case 67: case 76: case 85: case 94: case 97:								//colisionar con una pared
							if (a) {
								a = false;
								frenar(0.0);
								prota->vida = prota->vida - 20;
								rotarProta();
							}
							break;
						case 23: case 59:								//colisionar con una puerta hacia la derecha
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x + 220, prota->posicion.y);
								prota->sprite->setPosition(prota->posicion);
								scrollX = -1308;
								scrollY = 0;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 199:
							removeChild(nodeB, true);
							tieneObjeto = true;
							break;

						case 5: case 41:								//colisionar con una puerta hacia la izquierda
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 1308;
								scrollY = 0;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 14: case 50:							//colisionar con una puerta hacia arriba en IDIOMA NEL ¬¬
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 165);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 0;
								scrollY = 720;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;

						case 32: case 103:							//colisionar con una puerta hacia abajo en IDIOMA NEL ¬¬
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 0;
								scrollY = -720;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 49: case 88:							//colisionar con un cruce
							girar = true;
							posiCruce = nodeA->getPosition();
							break;
						case 25: case 70:							//colisionar con una curva de derecha-abajo
							posiCurva = nodeA->getPosition();
							if (prota->getOrientacion() == 'w') {
								prota->setOrientacion('s');
								prota->posicion = Vec2(posiCurva.x - 68, posiCurva.y);
							}
							else {
								prota->setOrientacion('e');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y + 50);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						case 61: case 34:							//colisionar con una curva de derecha-arriba
							posiCurva = nodeA->getPosition();
							if (prota->getOrientacion() == 'w') {
								prota->setOrientacion('n');
								prota->posicion = Vec2(posiCurva.x - 60, posiCurva.y);
							}
							else {
								prota->setOrientacion('e');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y - 40);
							}
							prota->cambiarSprite();
							prota->sprite->setPosition(prota->posicion);
							break;
						case 16: case 52:						//colisionar con una curva de izquierda-abajo
							posiCurva = nodeA->getPosition();
							if (prota->getOrientacion() == 'e') {
								prota->setOrientacion('s');
								prota->posicion = Vec2(posiCurva.x + 70, posiCurva.y);
							}
							else {
								prota->setOrientacion('w');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y + 50);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						case 43: case 79:							//colisionar con una curva de izquierda-arriba
							posiCurva = nodeA->getPosition();
							if (prota->getOrientacion() == 'e') {
								prota->setOrientacion('n');
								prota->posicion = Vec2(posiCurva.x + 68, posiCurva.y);
							}
							else {
								prota->setOrientacion('w');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y - 45);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						default:
							break;
						}
					}
				}
				//mismo código que antes, pero mirando si nodeB es prota
				else if (nodeB->getTag() == 5) {

					if (nodeA->getTag() > 109) { //cambiar
						if (placando == true) {
							for (int i = 0; i < enemigos.size(); i++) {
								if (enemigos[i] != nullptr) {
									if (enemigos[i]->sprite->getTag() == nodeA->getTag()) enemigos[i] = nullptr;
								}
							}
							removeChild(nodeA, true);	//eliminar al enemigo
							frenar(0.0);
						}
						else {
							prota->vida = prota->vida - 20;
							rotarProta();
						}
					}
					else {

						switch (nodeA->getTag())
						{
						case 4: case 6: case 7: case 15: case 24: case 48: case 57: case 66: case 68: case 73: case 75: case 77: case 84: case 86: case 93: case 95: case 96: case 102: case 104: case 105: case 31: case 40: case 58: case 67: case 76: case 85: case 94: case 97:								//colisionar con una pared
							if (a) {
								a = false;
								frenar(0.0);
								prota->vida = prota->vida - 20;
								rotarProta();
							}
							break;
						case 23: case 59:							//colisionar con una puerta hacia la derecha
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x + 220, prota->posicion.y);
								prota->sprite->setPosition(prota->posicion);
								scrollX = -1308;
								scrollY = 0;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;

						case 199:
							removeChild(nodeB, true);
							tieneObjeto = true;
							break;

						case 5: case 41:								//colisionar con una puerta hacia la izquierda
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 1308;
								scrollY = 0;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 14: case 50:						//colisionar con una puerta hacia arriba en IDIOMA NEL ¬¬
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 175);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 0;
								scrollY = 720;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 32: case 103:							//colisionar con una puerta hacia abajo EN IDIOMA NEL ¬¬
							if (cruzarPuerta == false) {
								prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
								prota->sprite->setPosition(prota->posicion);
								scrollX = 0;
								scrollY = -720;
								cruzarPuerta = true;
								velocidadenemiga = 5;
								if (cargaActual < 3) cargaActual++;
							}
							break;
						case 49: case 88:							//colisionar con un cruce
							girar = true;
							posiCruce = nodeB->getPosition();
							break;
						case 25: case 70:						//colisionar con una curva de derecha-abajo
							posiCurva = nodeB->getPosition();
							if (prota->getOrientacion() == 'w') {
								prota->setOrientacion('s');
								prota->posicion = Vec2(posiCurva.x - 68, posiCurva.y);
							}
							else {
								prota->setOrientacion('e');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y + 50);
							}
							prota->cambiarSprite();
							prota->sprite->setPosition(prota->posicion);
							break;
						case 61: case 34:							//colisionar con una curva de derecha-arriba
							posiCurva = nodeB->getPosition();
							if (prota->getOrientacion() == 'w') {
								prota->setOrientacion('n');
								prota->posicion = Vec2(posiCurva.x - 60, posiCurva.y);
							}
							else {
								prota->setOrientacion('e');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y - 40);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						case 16: case 52:							//colisionar con una curva de izquierda-abajo
							posiCurva = nodeB->getPosition();
							if (prota->getOrientacion() == 'e') {
								prota->setOrientacion('s');
								prota->posicion = Vec2(posiCurva.x + 70, posiCurva.y);
							}
							else {
								prota->setOrientacion('w');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y + 50);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						case 43: case 79:						//colisionar con una curva de izquierda-arriba
							posiCurva = nodeB->getPosition();
							if (prota->getOrientacion() == 'e') {
								prota->setOrientacion('n');
								prota->posicion = Vec2(posiCurva.x + 68, posiCurva.y);
							}
							else {
								prota->setOrientacion('w');
								prota->posicion = Vec2(posiCurva.x, posiCurva.y - 45);
							}
							prota->sprite->setPosition(prota->posicion);
							prota->cambiarSprite();
							break;
						default:
							break;
						}
					}
				}
			}
		}
		b = true;
		return true;
	}
}

bool GameScene::onContactEnd(PhysicsContact &contact) {
	//guardamos los nodos que han dejado de colisionar en variables
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB) { //si ninguno es null, porque si hemos embestido con un enemigo 
						  //lo habremos eliminado, por tanto un nodo sería null y el siguiente if daría error al comprobar
		
		if (nodeA->getTag() == 5 || nodeB->getTag() == 5) {
			if (nodeA->getTag() == 49 || nodeB->getTag() == 49 || nodeA->getTag() == 88 || nodeB->getTag() == 88) {  //si es un cruce, girar es false
				girar = false;
			}
			cruzarPuerta = false;
		}
	}
			 
		
		//poner cruzar puerta a false, porque ya habremos terminado de cruzarla
		return true;
}
