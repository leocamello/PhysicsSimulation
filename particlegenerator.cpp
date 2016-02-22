// particlegenerator.cpp
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Out 2009

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

#include "particlegenerator.h"

ParticleGenerator::ParticleGenerator()
{
	srand((int)time(NULL));
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::Initialize(
			   float m, float radius, int max,
			   float x, float y, float z)
{
	_mass = m;
	_radius = radius;
	_max = max;
	_position = Vector3(x, y, z);
	_generated = 0;

	for( int i = 0; i < max; i++ )
	{
		/*_particles[i] = NULL;*/
		float r, g, b;
		float px, py, pz;
		
		r = RandomNonNegativeNumber(1);
		g = RandomNonNegativeNumber(1);
		b = RandomNonNegativeNumber(1);

		px = RandomNumber(2) + _position.x;
		py = RandomNonNegativeNumber(500) + _position.y;
		pz = RandomNumber(2) + _position.z;

		_particles[i] = new Particle();
		_particles[i]->Initialize( 
			_mass, _radius,
			px, py, pz,
			r, g, b,
			Particle::ParticleType::ACTIVE);
	}
}

void ParticleGenerator::Update()
{
	/*float r, g, b;
	float px, py, pz;
	
	r = RandomNonNegativeNumber(1);
	g = RandomNonNegativeNumber(1);
	b = RandomNonNegativeNumber(1);

	px = RandomNumber(4);
	py = RandomNonNegativeNumber(25);
	pz = RandomNumber(4);

	_particles[_generated] = new Particle();
	_particles[_generated]->Initialize( 
		_mass, _radius,
		px, py, pz,
		r, g, b,
		Particle::ParticleType::ACTIVE);

	_generated++;*/
}

float ParticleGenerator::RandomNumber(int randmax)
{
	int random = rand();
	if(random%2==0)
	{
		random = -random;
	}
	float scale = random / (float)RAND_MAX;
	return scale * randmax;
}

float ParticleGenerator::RandomNonNegativeNumber(int randmax)
{
	float scale = rand() / (float)RAND_MAX;
	return scale * randmax;
}
