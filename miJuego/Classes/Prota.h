#pragma once
#include "cocos2d.h"
#include "Consumible.h"
#include "Objeto.h"





class Prota
{
	
	int vida;
	int energia;
	int velocidad;
	char orientacion;
	Consumible* consumible;
	Objeto* objeto;

public:
	//Sprite* sprite;
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

