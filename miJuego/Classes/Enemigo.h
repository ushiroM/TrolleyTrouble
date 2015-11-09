#pragma once

class Enemigo
{
	int vida;
	int ataque;
	int velocidad;
	int tipo;

public:
	Enemigo();
	~Enemigo();
	void atacar();
	void movimiento();

};

