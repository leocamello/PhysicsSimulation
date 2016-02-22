// cloth.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef CLOTH_H
#define CLOTH_H

#include "vector.h"
#include "particle.h"

class Cloth
{
public:
	Cloth();
	~Cloth();

	float _mass;
	int _dimU;
	int _dimV;
	int _faces;
	float _radius;
	Particle* _particles;
	float _red, _green, _blue;
	Particle::ParticleType _particleType;

	void Initialize(
		float mass, float radius,
		int nU, int nV,
		Vector3 p, Vector3 pU, Vector3 pV,		
		float r, float g, float b,
		Particle::ParticleType type);
	void Update();
	void Draw();
};

#endif