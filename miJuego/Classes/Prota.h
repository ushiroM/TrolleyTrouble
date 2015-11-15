#pragma once
#include "cocos2d.h";
#include "Consumible.h"
#include "Objeto.h"


class Prota : public cocos2d::Sprite
{
	Sprite* sprite;
	int vida;
	int energia;
	int velocidad;
	char orientacion;
	Consumible consumible;
	Objeto objeto;

public:

	Prota();
	~Prota();
	static Prota* create();
	void saltar();
	void girar();
	void embestir();
	void usarObjeto();
	void usarConsumible();
	void setOrientacion(char);
	char getOrientacion();

};

