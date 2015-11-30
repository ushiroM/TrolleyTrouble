#pragma once
#include "cocos2d.h"
#include "Consumible.h"
#include "Objeto.h"





class Prota
{
private:
	int vida;
	int energia;
	
	char orientacion;
	Consumible* consumible;
	Objeto* objeto;

public:
	Sprite* sprite;
	Sprite* imagenFrontal;
	Sprite* imagenIzquierda;
	Sprite* imagenDerecha;
	Sprite* imagenReverso;
	int velocidad;
	Vec2 posicion;
	Prota();
	~Prota();
	void saltar();
	void usarObjeto();
	void usarConsumible();
	void setOrientacion(char);
	char getOrientacion();
	void setVelocidad(int);
	void cambiarSprite();

};

