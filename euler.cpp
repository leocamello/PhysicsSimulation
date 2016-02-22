// euler.cpp
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "vector.h"
#include "particle.h"
#include "euler.h"

Euler::Euler()
{
}

void Euler::Integrate(Vector3 acceleration, Particle* particle)
{
	particle->_currPosition.x += particle->_currVelocity.x * _fixedTimeStep;
	particle->_currPosition.y += particle->_currVelocity.y * _fixedTimeStep;
	particle->_currPosition.z += particle->_currVelocity.z * _fixedTimeStep;
	
	particle->_currVelocity.x += acceleration.x * _fixedTimeStep;
	particle->_currVelocity.y += acceleration.y * _fixedTimeStep;
	particle->_currVelocity.z += acceleration.z * _fixedTimeStep;
}