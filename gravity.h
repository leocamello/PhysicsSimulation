// gravity.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef GRAVITY_H
#define GRAVITY_H

#include "vector.h"
#include "forcegenerator.h"

class Gravity : ForceGenerator
{
public:
	Gravity();
	~Gravity();

	Gravity(Vector3 acceleration);

	Vector3 _acceleration;

	void ApplyForce(Particle* particle);
};

#endif