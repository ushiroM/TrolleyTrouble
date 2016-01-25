#pragma once
#include "cocos2d.h"
#include "Consumible.h"
#include "Objeto.h"

class Prota
{
private:

	char orientacion;
	Consumible* consumible;
	Objeto* objeto;

public:
	int energia;
	int vida;
	Sprite* sprite;
	Sprite* imagenFrontal;
	Sprite* imagenIzquierda;
	Sprite* imagenDerecha;
	Sprite* imagenReverso;
	float velocidad;
	Vec2 posicion;
	Prota();
	~Prota();
	void setOrientacion(char);
	char getOrientacion();
	void setVelocidad(int);
	void cambiarSprite();

};

