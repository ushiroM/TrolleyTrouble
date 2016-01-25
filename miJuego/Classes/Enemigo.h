#include "cocos2d.h"

USING_NS_CC;

class Enemigo
{

private:
	int vida;
	int ataque;
	char orientacion;

public:
	int minX;
	int maxX;
	int minY;
	int maxY;
	int tipo;
	float velocidad;
	Vec2 posicion;
	Enemigo();
	void movimiento(int);
	Sprite* imagenIzquierda;
	Sprite* imagenDerecha;
	Sprite* sprite;
	void setOrientacion(char);
	char getOrientacion();
	void cambiarSprite();
};

