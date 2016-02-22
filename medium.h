// medium.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef MEDIUM_H
#define MEDIUM_H

#include "forcegenerator.h"

class Medium : ForceGenerator
{
public:
	Medium();
	~Medium();

	Medium(float dragCoefficient);

	float _dragCoefficient;

	void ApplyForce(Particle* particle);
};

#endif