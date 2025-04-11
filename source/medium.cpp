// medium.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/vector.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/medium.h"

Medium::Medium()
{
}

Medium::~Medium()
{
}

Medium::Medium(float dragCoefficient)
{
	_dragCoefficient = dragCoefficient;
}

void Medium::ApplyForce(Particle* particle)
{
	particle->_resultantForce.x += -_dragCoefficient * particle->_currVelocity.x;
	particle->_resultantForce.y += -_dragCoefficient * particle->_currVelocity.y;
	particle->_resultantForce.z += -_dragCoefficient * particle->_currVelocity.z;
}