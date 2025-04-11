// cube.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef CUBE_H
#define CUBE_H

#include "particle.h"

#define FACES 6
#define VERTICES 8

class Cube
{
public:
	Cube();
	~Cube();

	float _mass;
	float _radius;
	float _red, _green, _blue;
	Particle _particles[VERTICES];

	void Initialize(float mass, 
					float radius,
		float xMin, float xMax, 
		float yMin, float yMax, 
		float zMin, float zMax,
		float r, float g, float b,
		Particle::ParticleType type);
	void Update();
    void Draw();
};

#endif