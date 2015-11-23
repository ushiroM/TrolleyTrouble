#include "Prota.h"



Prota::Prota()
{
	sprite = Sprite::create("vagoneta.png");
	vida = 100;
	orientacion = 'e';
	velocidad = 10;
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

void Prota::cambiarSprite() {
	switch (orientacion) {
	
	case 'n':
		imagenReverso = Sprite::create("vagonetaReverso.png");
		sprite = imagenReverso;
		break;
	case 'e':
		imagenDerecha = Sprite::create("vagoneta.png");
		sprite = imagenDerecha;
		break;
	case 'w':
		imagenIzquierda = Sprite::create("vagonetaIzquierdo.png");
		sprite = imagenIzquierda;
		break;
	case 's':
		imagenFrontal = Sprite::create("vagonetaFrontal.png");
		sprite = imagenFrontal;
		break;
	
	
	
	
	}



}
