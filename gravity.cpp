// gravity.cpp
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "particle.h"
#include "gravity.h"

Gravity::Gravity()
{
	_acceleration = Vector3(0.0f, -9.8f, 0.0f);
}

Gravity::~Gravity()
{
}

Gravity::Gravity(Vector3 acceleration)
{
	_acceleration = acceleration;
}

void Gravity::ApplyForce(Particle* particle)
{
	particle->_resultantForce.x += particle->_mass * _acceleration.x;
	particle->_resultantForce.y += particle->_mass * _acceleration.y;
	particle->_resultantForce.z += particle->_mass * _acceleration.z;
}