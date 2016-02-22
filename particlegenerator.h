// particlegenerator.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Out 2009

#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include "vector.h"
#include "particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();

	int _max;
	float _mass;
	float _radius;
	int _generated;
	Vector3 _position;
	Particle* _particles[128];


    void Initialize(
		float m, 
		float radius, 
		int max,
		float x, float y, float z);
	void Update();

private:
	float RandomNumber(int randmax);
	float RandomNonNegativeNumber(int randmax);
};

#endif