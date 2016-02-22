// integrator.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "vector.h"
#include "particle.h"
#include "integrator.h"

Integrator::Integrator()
{
	_fixedTimeStep = 0.05f;
}

void Integrator::Integrate(Vector3 acceleration, Particle* particle)
{
}