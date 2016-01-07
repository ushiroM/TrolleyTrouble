#include "GameScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"

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
	Size protasize = Size(prota->sprite->getBoundingBox().size.width - 40, prota->sprite->getBoundingBox().size.height - 40);
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
	enemigo5->sprite->setTag(111);
	enemigo5->tipo = 1;
	enemigo5->sprite->setOpacity(75);
	auto bodyenemigo5 = PhysicsBody::createBox(enemigo5->sprite->getBoundingBox().size/2);
	bodyenemigo5->setContactTestBitmask(true);
	bodyenemigo5->setDynamic(true);
	enemigo5->sprite->setPhysicsBody(bodyenemigo5);
	enemigo5->sprite->setPosition(Vec2(750,500));
	addChild(enemigo5->sprite);
	enemigos.push_back(enemigo5);
	

	Enemigo* enemigo4 = new Enemigo();
	enemigo4->sprite = Sprite::create("enemifo.png");
	enemigo4->sprite->setTag(110);
	enemigo4->tipo = 1;
	enemigo4->sprite->setOpacity(75);
	auto bodyenemigo4 = PhysicsBody::createBox(enemigo4->sprite->getBoundingBox().size/2);
	bodyenemigo4->setContactTestBitmask(true);
	bodyenemigo4->setDynamic(true);
	enemigo4->sprite->setPhysicsBody(bodyenemigo4);
	enemigo4->sprite->setPosition(Vec2(750, 110));
	addChild(enemigo4->sprite);
	enemigos.push_back(enemigo4);
	
	//crear el HUD
	barraEnergia->setPosition(Vec2(55, 660));
	barraEnergia->setAnchorPoint(Vec2(0.f, 0.5f));
	addChild(barraEnergia);

	barraVida->setPosition(Vec2(55, 670));
	barraVida->setAnchorPoint(Vec2(0.f, 0.5f));
	addChild(barraVida);

	hud->setPosition(Vec2(190, 670));
	addChild(hud);

	

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
}

//función que añade cajas de colisión a los tiles, y un tag para las colisiones
void GameScene::addColision(Sprite * sprite, int tipo)
{	
	PhysicsBody* bodye;
	switch (tipo){
	
	case 25: case 34: case 43: case 52: case 61: case 70: case 79: case 16:
		bodye = PhysicsBody::createBox(sprite->getBoundingBox().size / 2);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
		break;
		

	case 49: case 88:	//si el tile es un cruce de vías 
		bodye = PhysicsBody::createBox(sprite->getBoundingBox().size / 2);
		bodye->setContactTestBitmask(true);
		bodye->setDynamic(false);
		sprite->setTag(tipo);
		sprite->setPhysicsBody(bodye);
		break;

	/*case 48: case 66: case 68: case 86:  //paredes horizontales
		bodye = PhysicsBody::createBox(Size(sprite->getBoundingBox().size.width/10, sprite->getBoundingBox().size.height));
		break;
	
	case 57: case 77: case 24: case 4:
		bodye = PhysicsBody::createBox(Size(sprite->getBoundingBox().size.width, sprite->getBoundingBox().size.height/10));
		break;*/

	default:	//cualquier otro tile
		//if (tipo != 48 && tipo != 66 && tipo != 68 && tipo != 86 && tipo != 57 && tipo != 77 && tipo != 24 && tipo != 4) {
			bodye = PhysicsBody::createBox(sprite->getBoundingBox().size);
			bodye->setContactTestBitmask(true);
			bodye->setDynamic(false);
			sprite->setTag(tipo);
			sprite->setPhysicsBody(bodye);
		//}
		break;
	}
	
}

//función que se ejecuta periódicamente
void GameScene::update(float dt) {

	

	a = true;

	for (int i = 0; i < enemigos.size(); i++) {
		if (enemigos[i] != nullptr) {
			if (enemigos[i]->sprite->getScaleX() == -1) enemigos[i]->sprite->setPosition(enemigos[i]->sprite->getPositionX() - 5, enemigos[i]->sprite->getPositionY());
			else enemigos[i]->sprite->setPosition(enemigos[i]->sprite->getPositionX() + 5, enemigos[i]->sprite->getPositionY());
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
bool GameScene::onContactEnd(PhysicsContact &contact) {
	//guardamos los nodos que han dejado de colisionar en variables
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB) { //si ninguno es null, porque si hemos embestido con un enemigo 
		//lo habremos eliminado, por tanto un nodo sería null y el siguiente if daría error al comprobar
		if (nodeA->getTag() == 49 || nodeB->getTag() == 49 || nodeA->getTag() == 88 || nodeB->getTag() == 88) girar = false; //si es un cruce, girar es false
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
			if (nodeA->getTag() > 109 || nodeB->getTag() > 109) { //cambiar
				if (nodeA->getTag() > 109 && (nodeB->getTag() == 4 || nodeB->getTag() == 6 || nodeB->getTag() == 7 || nodeB->getTag() == 15 || nodeB->getTag() == 24 || nodeB->getTag() == 48 || nodeB->getTag() == 57 || nodeB->getTag() == 66 || nodeB->getTag() == 68 || nodeB->getTag() == 73 || nodeB->getTag() == 75 || nodeB->getTag() == 77 || nodeB->getTag() == 84 || nodeB->getTag() == 86 || nodeB->getTag() == 93 || nodeB->getTag() == 95 || nodeB->getTag() == 96 || nodeB->getTag() == 102 || nodeB->getTag() == 104 || nodeB->getTag() == 105 || nodeB->getTag() == 31 || nodeB->getTag() == 40 || nodeB->getTag() == 58 || nodeB->getTag() == 67 || nodeB->getTag() == 76 || nodeB->getTag() == 85 || nodeB->getTag() == 94 || nodeB->getTag() == 97)) {
					for (int i = 0;i < enemigos.size();i++) {
						if (enemigos[i] != nullptr) {
							if (enemigos[i]->sprite->getTag() == nodeA->getTag()) {
								if (enemigos[i]->sprite->getScaleX() == -1) enemigos[i]->sprite->setScaleX(1);
								else enemigos[i]->sprite->setScaleX(-1);
								break;
							}
						}
					}
				}
				else if (nodeB->getTag() > 109 && (nodeA->getTag() == 4 || nodeA->getTag() == 6 || nodeA->getTag() == 7 || nodeA->getTag() == 15 || nodeA->getTag() == 24 || nodeA->getTag() == 48 || nodeA->getTag() == 57 || nodeA->getTag() == 66 || nodeA->getTag() == 68 || nodeA->getTag() == 73 || nodeA->getTag() == 75 || nodeA->getTag() == 77 || nodeA->getTag() == 84 || nodeA->getTag() == 86 || nodeA->getTag() == 93 || nodeA->getTag() == 95 || nodeA->getTag() == 96 || nodeA->getTag() == 102 || nodeA->getTag() == 104 || nodeA->getTag() == 105 || nodeA->getTag() == 31 || nodeA->getTag() == 40 || nodeA->getTag() == 58 || nodeA->getTag() == 67 || nodeA->getTag() == 76 || nodeA->getTag() == 85 || nodeA->getTag() == 94 || nodeA->getTag() == 97)) { //cambiar
					for (int i = 0;i < enemigos.size();i++) {
						if (enemigos[i] != nullptr) {
							if (enemigos[i]->sprite->getTag() == nodeB->getTag()) {
								if (enemigos[i]->sprite->getScaleX() == -1) enemigos[i]->sprite->setScaleX(1);
								else enemigos[i]->sprite->setScaleX(-1);
								break;
							}
						}
					}
				}
			}


			if (nodeA->getTag() == 5) { //si nodeA es el prota
				
				if (nodeB->getTag() > 109) { //cambiar
						if (placando == true) {
							for (int i = 0;i < enemigos.size();i++) {
								if (enemigos[i] != nullptr) {
									if (enemigos[i]->sprite->getTag() == nodeB->getTag()) enemigos[i] = nullptr;
								}
							}
							removeChild(nodeB, true);	//eliminar al enemigo
							frenar(0.0);
						}else{
							prota->vida = prota->vida - 20;
							rotarProta();
						}
				}else{

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
						}
						break;
					case 5: case 41:								//colisionar con una puerta hacia la izquierda
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 1308;
							scrollY = 0;
							cruzarPuerta = true;
						}
						break;
					case 14: case 50:							//colisionar con una puerta hacia arriba en IDIOMA NEL ¬¬
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 165);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 0;
							scrollY = 720;
							cruzarPuerta = true;
						}
						break;
					
					case 32: case 103:							//colisionar con una puerta hacia abajo en IDIOMA NEL ¬¬
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 0;
							scrollY = -720;
							cruzarPuerta = true;
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
							prota->posicion = Vec2(posiCurva.x, posiCurva.y -40);
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
						for (int i = 0;i < enemigos.size();i++) {
							if (enemigos[i] != nullptr) {
								if (enemigos[i]->sprite->getTag() == nodeA->getTag()) enemigos[i] = nullptr;
							}
						}
						removeChild(nodeA, true);	//eliminar al enemigo
						frenar(0.0);
					}else{
						prota->vida = prota->vida - 20;
						rotarProta();
					}
				}else{

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
						}
						break;
					case 5: case 41:								//colisionar con una puerta hacia la izquierda
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x - 220, prota->posicion.y);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 1308;
							scrollY = 0;
							cruzarPuerta = true;
						}
						break;
					case 14: case 50:						//colisionar con una puerta hacia arriba en IDIOMA NEL ¬¬
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 175);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 0;
							scrollY = 720;
							cruzarPuerta = true;
						}
						break;
					case 32: case 103:							//colisionar con una puerta hacia abajo EN IDIOMA NEL ¬¬
						if (cruzarPuerta == false) {
							prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 165);
							prota->sprite->setPosition(prota->posicion);
							scrollX = 0;
							scrollY = -720;
							cruzarPuerta = true;
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
							prota->posicion = Vec2(posiCurva.x -68, posiCurva.y);
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