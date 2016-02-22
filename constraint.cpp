// constraint.cpp
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "graphics.h"

#include "vector.h"
#include "particle.h"
#include "constraint.h"

Constraint::Constraint()
{
}

Constraint::~Constraint()
{
}

Constraint::Constraint(float length, Particle* particleA, Particle* particleB)
{
	_length = length;
	_particleA = particleA;
	_particleB = particleB;
}

void Constraint::SatisfyConstraint()
{
	_direction.x = _particleB->_currPosition.x - _particleA->_currPosition.x;
	_direction.y = _particleB->_currPosition.y - _particleA->_currPosition.y;
	_direction.z = _particleB->_currPosition.z - _particleA->_currPosition.z;


	if(_direction.x != 0.0f || _direction.y != 0.0f || _direction.z != 0.0f)
	{
		_currLength = _direction.Length();
		_direction.Normalize();

		_moveVector.x = 0.5f * (( _currLength - _length) * _direction.x);		
		_moveVector.y = 0.5f * (( _currLength - _length) * _direction.y);
		_moveVector.z = 0.5f * (( _currLength - _length) * _direction.z);

		_particleA->_currPosition += _moveVector;
		_particleB->_currPosition += -_moveVector;
	}
}