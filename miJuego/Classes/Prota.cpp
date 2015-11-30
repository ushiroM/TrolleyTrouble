#include "Prota.h"



Prota::Prota()
{
	sprite = Sprite::create("vagoneta.png");
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
		sprite->setTexture("vagonetaReverso.png");
		break;
	case 'e':
		sprite->setTexture("vagoneta.png");
		break;
	case 'w':
		sprite->setTexture("vagonetaIzquierdo.png");
		break;
	case 's':
		sprite->setTexture("vagonetaFrontal.png");
		break;
	
	
	
	
	}



}
