#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Prota.h"
#include "Enemigo.h"

class GameScene: public cocos2d::Layer
{
private:
	Prota* prota;
	EventKeyboard::KeyCode _pressedKey;
	PhysicsWorld *mWorld;
	PhysicsBody *body;
	int velocidadanterior = 1;
	bool placando = false;
	Sprite* barraEnergia = Sprite::create("energia.png");
	Sprite* barraVida = Sprite::create("vida.png");
	Sprite* hud = Sprite::create("hud/hudtile.png");
	
	bool b = true;
	bool a = true;
	TMXTiledMap* map = TMXTiledMap::create("piso.tmx");
	bool cruzarPuerta;
	float scrollX;
	float scrollY;
	bool girar = false;
	Vec2 posiCruce;
	Vec2 posiCurva;
	std::vector<Enemigo*> enemigos;

	
	
public:
	static cocos2d::Scene* createScene();
	void goToPauseScene(Ref *pSender);
	void goToGameOverScene(Ref *pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void update(float dt);
	virtual bool init();
	void setPhysicsWorld(PhysicsWorld *world);
	bool onContactBegin(PhysicsContact &contact);
	bool onContactEnd(PhysicsContact &contact);
	void frenar(float);
	void crearSala();
	void addColision(Sprite* sprite, int tipo);
	void rotarProta();
	void centerViewport(float scrollX, float scrollY);
	CREATE_FUNC(GameScene);

};

#endif

