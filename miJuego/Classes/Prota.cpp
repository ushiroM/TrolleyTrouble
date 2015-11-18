#include "Prota.h"
#include "Assets.h"


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
