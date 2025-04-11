// euler.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef EULER_H
#define EULER_H

#include "integrator.h"

struct Vector3;

class Euler : Integrator
{
public:
	Euler();
	
    void Integrate(Vector3 acceleration, Particle* particle);
};

#endif