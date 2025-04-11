// spring.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"

#include "PhysicsSimulation/vector.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/spring.h"

Spring::Spring()
{
}

Spring::~Spring()
{
}

Spring::Spring(float stiffness, float damping, Particle* particleA, Particle* particleB)
{
	_stiffness = stiffness;
	_damping = damping;
	_particleA = particleA;
	_particleB = particleB;

	_direction.x = _particleA->_currPosition.x - _particleB->_currPosition.x;
	_direction.y = _particleA->_currPosition.y - _particleB->_currPosition.y;
	_direction.z = _particleA->_currPosition.z - _particleB->_currPosition.z;

	_restLength = _direction.Length();
}

Spring::Spring(float stiffness, float damping, Particle* particleA, Particle* particleB, float restLength)
{
	_stiffness = stiffness;
	_damping = damping;
	_particleA = particleA;
	_particleB = particleB;
	_restLength = restLength;
}

void Spring::Update()
{
}

void Spring::Draw()
{
	float coord1[3] = {
		_particleA->_currPosition.x,
		_particleA->_currPosition.y,
		_particleA->_currPosition.z};
	float coord2[3] = {
		_particleB->_currPosition.x,
		_particleB->_currPosition.y,
		_particleB->_currPosition.z};

	Graphics::DrawSpring(
		_direction.Length(), _restLength, coord1, coord2);
}

void Spring::ApplyForce(Particle particle)
{
	_direction.x = _particleA->_currPosition.x - _particleB->_currPosition.x;
	_direction.y = _particleA->_currPosition.y - _particleB->_currPosition.y;
	_direction.z = _particleA->_currPosition.z - _particleB->_currPosition.z;

	if(_direction.x != 0.0f || _direction.y != 0.0f || _direction.z != 0.0f)
	{
		_currLength = _direction.Length();
		_direction.Normalize();

		_force.x = -_stiffness * (( _currLength - _restLength) * _direction.x);		
		_force.y = -_stiffness * (( _currLength - _restLength) * _direction.y);
		_force.z = -_stiffness * (( _currLength - _restLength) * _direction.z);

		Vector3 velocity;
		velocity.x = _particleA->_currVelocity.x - _particleB->_currVelocity.x;
		velocity.y = _particleA->_currVelocity.y - _particleB->_currVelocity.y;
		velocity.z = _particleA->_currVelocity.z - _particleB->_currVelocity.z;

		_force.x += -_damping * Dot(velocity, _direction) * _direction.x;
		_force.y += -_damping * Dot(velocity, _direction) * _direction.y;
		_force.z += -_damping * Dot(velocity, _direction) * _direction.z;

		_particleA->_resultantForce += _force;
		_particleB->_resultantForce += - _force;
	}
}