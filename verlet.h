// verlet.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef VERLET_H
#define VERLET_H

#include "integrator.h"

struct Vector3;

class Verlet : Integrator
{
public:
	Verlet();
	~Verlet();

	float _drag;
	
    void Integrate(Vector3 acceleration, Particle* particle);
};

#endif