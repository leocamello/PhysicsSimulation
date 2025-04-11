// cube.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"
#include "PhysicsSimulation/cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Initialize(float mass, 
					  float radius,
		float xMin, float xMax, 
		float yMin, float yMax, 
		float zMin, float zMax,
		float r, float g, float b,
		Particle::ParticleType type)
{
	_mass = mass/8;
	_radius = radius;
	_particles[0].Initialize(_mass, _radius, xMin, yMax, zMin, r, g, b, type);
	_particles[1].Initialize(_mass, _radius, xMax, yMax, zMin, r, g, b, type);
	_particles[2].Initialize(_mass, _radius, xMax, yMax, zMax, r, g, b, type);
	_particles[3].Initialize(_mass, _radius, xMin, yMax, zMax, r, g, b, type);
	_particles[4].Initialize(_mass, _radius, xMin, yMin, zMin, r, g, b, type);
	_particles[5].Initialize(_mass, _radius, xMax, yMin, zMin, r, g, b, type);
	_particles[6].Initialize(_mass, _radius, xMax, yMin, zMax, r, g, b, type);
	_particles[7].Initialize(_mass, _radius, xMin, yMin, zMax, r, g, b, type);
}

void Cube::Update()
{
}

void Cube::Draw()
{
	float coord[FACES * 4];
	for(int i = 0; i < VERTICES; i++)
	{
		coord[i*3+0] = _particles[i]._currPosition.x; 
		coord[i*3+1] = _particles[i]._currPosition.y; 
		coord[i*3+2] = _particles[i]._currPosition.z;
	}
	
	unsigned int quads[FACES * 4] = 
	{
		0, 3, 2, 1,
		4, 5, 6, 7,
		0, 1, 5, 4,
		1, 2, 6, 5,
		2, 3, 7, 6,
		0, 4, 7, 3
	};

	Graphics::DrawQuads(
		FACES * 4, quads, coord, _red, _green, _blue);
}