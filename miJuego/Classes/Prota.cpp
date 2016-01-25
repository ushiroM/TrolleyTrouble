#include "Prota.h"



Prota::Prota()
{
	sprite = Sprite::create("prota/lateralDerecho.png");
	vida = 100;
	orientacion = 'e';
	velocidad = 1;
	energia = 100;
		
}

Prota::~Prota()
{
}

void Prota::setOrientacion(char orientacion) {
	this->orientacion = orientacion;


}

char Prota::getOrientacion() {
	return this->orientacion;

}

void Prota::setVelocidad(int velocidad) {
	this->velocidad = velocidad;
}

void Prota::cambiarSprite() {
	switch (orientacion) {
	
	case 'n':
		sprite->setTexture("prota/reverso.png");
		break;
	case 'e':
		sprite->setTexture("prota/lateralDerecho.png");
		break;
	case 'w':
		sprite->setTexture("prota/lateralIzquierdo.png");
		break;
	case 's':
		sprite->setTexture("prota/frontal.png");
		break;

	}
}
