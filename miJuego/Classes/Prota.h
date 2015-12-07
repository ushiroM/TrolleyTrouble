#pragma once
#include "cocos2d.h"
#include "Consumible.h"
#include "Objeto.h"





class Prota
{
private:
	int vida;
	
	
	char orientacion;
	Consumible* consumible;
	Objeto* objeto;

public:
	int energia;
	Sprite* sprite;
	Sprite* imagenFrontal;
	Sprite* imagenIzquierda;
	Sprite* imagenDerecha;
	Sprite* imagenReverso;
	float velocidad;
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

