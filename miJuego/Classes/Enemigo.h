#include "cocos2d.h"

USING_NS_CC;

class Enemigo
{
	int vida;
	int ataque;
	int velocidad;
	int tipo;


public:
	Enemigo();
	void atacar();
	void movimiento();
	Sprite* sprite;
};

