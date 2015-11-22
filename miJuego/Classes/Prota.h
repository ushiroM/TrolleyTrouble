#pragma once
#include "cocos2d.h"
#include "Consumible.h"
#include "Objeto.h"





class Prota
{
private:
	int vida;
	int energia;
	int velocidad;
	char orientacion;
	Consumible* consumible;
	Objeto* objeto;

public:
	Sprite* sprite;
	Vec2 posicion;
	Prota();
	~Prota();
	void saltar();
	void girar();
	void embestir();
	void usarObjeto();
	void usarConsumible();
	void setOrientacion(char);
	char getOrientacion();

};

