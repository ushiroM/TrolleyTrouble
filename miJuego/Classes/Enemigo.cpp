#include "Enemigo.h"

Enemigo::Enemigo()
{
	velocidad = 1;
}

void Enemigo::setOrientacion(char ori) {
	this->orientacion = ori;
}

char Enemigo::getOrientacion() {
	return this->orientacion;
}

void Enemigo::movimiento() {
	
	/*switch (tipo) {
	case 1: case 2:
		
		if (this->sprite->getPositionX() > maxX) {
			this->orientacion = 'w';
			this->sprite->setFlippedX(true);
			this->sprite->setPositionX(maxX);
		}else if (this->sprite->getPositionX() < minX) {
			this->orientacion = 'e';
			this->sprite->setFlippedX(false);
			this->sprite->setPositionX(minX);
		}

		if (this->orientacion == 'e') {
			this->sprite->setPosition(Vec2(this->sprite->getPositionX() + 5, this->sprite->getPositionY()));
		}else {
			this->sprite->setPosition(Vec2(this->sprite->getPositionX() - 5, this->sprite->getPositionY()));
		}
		break;

	case 3:
		
		if (this->sprite->getPositionY() > maxY) {
		this->orientacion = 's';
		this->sprite->setPositionY(maxY);
		}
		else if (this->sprite->getPositionY() < minY) {
		this->orientacion = 'n';
		this->sprite->setPositionY(minY);
		}
		if (this->orientacion == 'n') {
			this->sprite->setPosition(Vec2(this->sprite->getPositionX(), this->sprite->getPositionY() + 5));
		}
		else {
			this->sprite->setPosition(Vec2(this->sprite->getPositionX(), this->sprite->getPositionY() - 5));
		}
		break;
	default:
		break;
	}*/
}


void Enemigo::cambiarSprite() {
	switch (orientacion) {
		case 'n':
			sprite->setTexture("enemigos/cosa.png");
			break;
		case 'e':
			sprite->setTexture("enemigos/cosa.png");
			break;
		case 'w':
			sprite->setTexture("enemigos/cosa.png");
			break;
		case 's':
			sprite->setTexture("enemigos/cosa.png");
			break;
	}
}
