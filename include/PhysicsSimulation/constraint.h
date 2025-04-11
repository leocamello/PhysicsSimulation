// constraint.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

class Constraint
{
public:
	Constraint();
	~Constraint();
	Constraint(float length, Particle* particleA, Particle* particleB);

	float _length;
	float _currLength;
	Vector3 _direction;
	Vector3 _moveVector;
	Particle* _particleA;
	Particle* _particleB;

	void SatisfyConstraint();
};

#endif