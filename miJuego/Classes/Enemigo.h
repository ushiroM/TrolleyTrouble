#include "cocos2d.h"

USING_NS_CC;

class Enemigo
{
private:
	int vida;
	int ataque;
	int velocidad;
	


public:
	int tipo;
	Vec2 posicion;
	Enemigo();
	void atacar();
	void movimiento();
	Sprite* sprite;
};

