// euler.cpp
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "vector.h"
#include "particle.h"
#include "verlet.h"

Verlet::Verlet()
{
	_drag = 0.01f;
}

void Verlet::Integrate(Vector3 acceleration, Particle* particle)
{
	Vector3 position;

	position.x = (2 - _drag) * particle->_currPosition.x;
	position.y = (2 - _drag) * particle->_currPosition.y;
	position.z = (2 - _drag) * particle->_currPosition.z;

	position.x -= (1 - _drag) * particle->_prevPosition.x;
	position.y -= (1 - _drag) * particle->_prevPosition.y;
	position.z -= (1 - _drag) * particle->_prevPosition.z;
	
	acceleration.x *= _fixedTimeStep * _fixedTimeStep;
	acceleration.y *= _fixedTimeStep * _fixedTimeStep;
	acceleration.z *= _fixedTimeStep * _fixedTimeStep;

	position += acceleration;
	
	particle->_prevPosition = particle->_currPosition;
	particle->_currPosition = position;
}