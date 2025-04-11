// spring.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef SPRING_H
#define SPRING_H

#include "forcegenerator.h"

class Spring : ForceGenerator
{
public:
	Spring();
	~Spring();
	Spring(float stiffness, float damping, Particle* particleA, Particle* particleB);
	Spring(float stiffness, float damping, Particle* particleA, Particle* particleB, float restLength);

	float _damping;
	float _stiffness;
	float _restLength;
	float _currLength;
	Vector3 _force;
	Vector3 _direction;
	Particle* _particleA;
	Particle* _particleB;

	void Update();
	void Draw();

	void ApplyForce(Particle particle);
};

#endif