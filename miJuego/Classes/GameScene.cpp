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
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //que se vean las colisiones de las cajas
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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//crear el prota y aádirle su cuerpo de box2d
	prota = new Prota();
	Size protasize = Size(prota->sprite->getBoundingBox().size.width - 20, prota->sprite->getBoundingBox().size.height - 20);
	auto body = PhysicsBody::createBox(protasize);
	prota->sprite->setTag(5);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	prota->sprite->setPhysicsBody(body);
	prota->posicion = Vec2(218, 280);
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);

	//crear el enemigo
	Enemigo* enemigo5 = new Enemigo();
	enemigo5->sprite = Sprite::create("enemifo.png");
	enemigo5->sprite->setTag(99);
	auto bodyenemigo5 = PhysicsBody::createBox(enemigo5->sprite->getBoundingBox().size);
	bodyenemigo5->setContactTestBitmask(true);
	bodyenemigo5->setDynamic(false);
	enemigo5->sprite->setPhysicsBody(bodyenemigo5);
	enemigo5->sprite->setPosition(Vec2(750,500));
	addChild(enemigo5->sprite);

	//crear el HUD
	barraEnergia->setPosition(Vec2(0, 660));
	addChild(barraEnergia);

	energyLabel->setPosition(Vec2(270, 660));
	addChild(energyLabel);

	lifeLabel->setPosition(Vec2(270, 700));
	addChild(lifeLabel);

	barraVida->setPosition(Vec2(0, 700));
	addChild(barraVida);

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
				prota->posicion = Vec2(posicruce.x, posicruce.y - 50);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posicruce.x, posicruce.y + 50);
				prota->sprite->setPosition(prota->posicion);
			}
			
			
			prota->setOrientacion('w');
			prota->cambiarSprite();
			
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w' && girar == true) {
			
			if (prota->getOrientacion() == 's') {
				prota->posicion = Vec2(posicruce.x, posicruce.y - 50);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posicruce.x, posicruce.y + 50);
				prota->sprite->setPosition(prota->posicion);
			}
			prota->setOrientacion('e');
			prota->cambiarSprite();
		}
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's' && girar == true) {
			if (prota->getOrientacion() == 'w') {
				prota->posicion = Vec2(posicruce.x - 63, posicruce.y);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posicruce.x + 65, posicruce.y);
				prota->sprite->setPosition(prota->posicion);
			}
			
			
			prota->setOrientacion('n');
			prota->cambiarSprite();
			
		}
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n' && girar == true) {
			if (prota->getOrientacion() == 'w') {
				prota->posicion = Vec2(posicruce.x - 63, posicruce.y);
				prota->sprite->setPosition(prota->posicion);
			}

			else {
				prota->posicion = Vec2(posicruce.x + 65, posicruce.y);
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
			if (tileGID != 0 && tileGID != 1 && tileGID != 6 && tileGID != 3){ //si no es un tile de raíl recto, vacío, o de suelo
				addColision(layer->getTileAt(Vec2(x, y)), tileGID); //añadirle una caja de colisión al tile
			}
		}
	}
}

//función que añade cajas de colisión a los tiles, y un tag para las colisiones
void GameScene::addColision(Sprite * sprite, int tipo)
{	
	if (tipo == 11) { //si el tile es un cruce de vías 
		auto bodye = PhysicsBody::createBox(sprite->getBoundingBox().size/2);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
	}
	else { //cualquier otro tile
		auto bodye = PhysicsBody::createBox(sprite->getBoundingBox().size);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
	}
}

//función que se ejecuta periódicamente
void GameScene::update(float dt) {

	if (cruzarPuerta == true) {
		centerViewport(scrollX, scrollY); //cambair la cámara al cruzar puertas
	}

	a = true;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//actualizar la barra de vida según la vida actual
	barraEnergia->setScaleX(prota->energia*4);
	if (prota->energia < 100) prota->energia++;
	barraVida->setScaleX(prota->vida * 4);
	
	//mover al prota según la dirección que mira
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

	//si no queda vida, ir a la pantalla de game over
	if (prota->vida <= 0) goToGameOverScene(this); //HUAAAAAAAAAAOOOO
}

//función que centra la cámara en la sala actual
void GameScene::centerViewport(float scrollX, float scrollY) {
	
	float x = this->getPositionX();
	float y = this->getPositionY();
	this->setPosition(Vec2(x+scrollX, y+scrollY));
}

//evento que se lanza cuando dos cuerpos de box2d dejan de colisionar
bool GameScene::onContactEnd(PhysicsContact &contact) {
	//guardamos los nodos que han dejado de colisionar en variables
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB) { //si ninguno es null, porque si hemos embestido con un enemigo 
		//lo habremos eliminado, por tanto un nodo sería null y el siguiente if daría error al comprobar
		if (nodeA->getTag() == 11 || nodeB->getTag() == 11) girar = false; //si es un cruce, girar es false
	}
	cruzarPuerta = false; //poner cruzar puerta a false, porque ya habremos terminado de cruzarla
	return true;
}

//evento que se lanza al empezar a colisionar dos cuerpos de box2d
bool GameScene::onContactBegin(PhysicsContact &contact) {

	float x = map->getPositionX();
	float y = map->getPositionY();
	if (b) {	
		b = false;
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();

		if (nodeA && nodeB) //si ninguno es null
		{
			if (nodeA->getTag() == 5) { //si nodeA es el prota
				switch (nodeB->getTag())
				{
				case 99:							//colisionar con un enemigo
					if (placando == true) {
						removeChild(nodeB, true);	//eliminar al enemigo
						frenar(0.0);
					}
					else {
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 10:								//colisionar con una pared
					if (a) {
						a = false;
						frenar(0.0);
						//prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 9:								//colisionar con una puerta hacia la derecha
					prota->posicion = Vec2(prota->posicion.x + 220, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = -1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 5:								//colisionar con una puerta hacia la izquierda
					prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 2:								//colisionar con una puerta hacia arriba
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 165);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = 720;
					cruzarPuerta = true;
					break;
				case 4:								//colisionar con una puerta hacia abajo
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = -720;
					cruzarPuerta = true;
					break;
				case 11:							//colisionar con un cruce
					girar = true;
					posicruce = nodeA->getPosition();
					break;
				default:
					break;
				}
			}
			//mismo código que antes, pero mirando si nodeB es prota
			else if (nodeB->getTag() == 5) {
				switch (nodeA->getTag())
				{
				case 99:					//colisionar con enemigo
					if (placando == true) {
						removeChild(nodeA, true);
						frenar(0.0);
					}
					else {
						prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 10:						//colisionar con una pared
					if (a) {
						a = false;
						frenar(0.0);
						//prota->vida = prota->vida - 20;
						rotarProta();
					}
					break;
				case 9:								//colisionar con una puerta hacia la derecha
					prota->posicion = Vec2(prota->posicion.x + 220, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = -1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 5:								//colisionar con una puerta hacia la izquierda
					prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 1308;
					scrollY = 0;
					cruzarPuerta = true;
					break;
				case 2:								//colisionar con una puerta hacia arriba
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 175);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = 720;
					cruzarPuerta = true;
					break;
				case 4:								//colisionar con una puerta hacia abajo
					prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
					prota->sprite->setPosition(prota->posicion);
					scrollX = 0;
					scrollY = -720;
					cruzarPuerta = true;
					break;
				case 11:							//colisionar con un cruce
					girar = true;
					posicruce = nodeB->getPosition();
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