// particle.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.h"

class Particle
{
public:
	enum ParticleType
	{
		PASSIVE,
		ACTIVE
	};

	Particle();
	~Particle();

	float _mass;
	float _radius;
	Vector3 _currPosition;
	Vector3 _prevPosition;
	Vector3 _currVelocity;
	Vector3 _resultantForce;
	float _red, _green, _blue;
	ParticleType _particleType;

    void Initialize(
		float m, 
		float radius, 
		float x, float y, float z,		
		float r, float g, float b,
		ParticleType type);
	void Initialize(
		float m, 
		float radius, 
		float px, float py, float pz,
		float vx, float vy, float vz,
		float r, float g, float b,
		ParticleType type);
	void Update();
	void DrawPoint();
	void DrawSphere();
	void ResetForces();
};

#endif