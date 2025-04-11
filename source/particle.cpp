// particle.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"

#include "PhysicsSimulation/particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Initialize(
		float m, 
		float radius, 
		float x, float y, float z,		
		float r, float g, float b,
		ParticleType type)
{
	_red = r;
	_green = g;
	_blue = b;
	_mass = m;
	_radius = radius;
	_currPosition = Vector3(x, y, z);
	_currVelocity = Vector3(0.0f, 0.0f, 0.0f);
	_resultantForce = Vector3(0.0f, 0.0f, 0.0f);
	_prevPosition = _currPosition;
	_particleType = type;
}

void Particle::Initialize(
		float m, 
		float radius, 
		float px, float py, float pz,
		float vx, float vy, float vz,
		float r, float g, float b,
		ParticleType type)
{
	_red = r;
	_green = g;
	_blue = b;
	_mass = m;
	_radius = radius;
	_currPosition = Vector3(px, py, pz);
	_currVelocity = Vector3(vx, vy, vz);
	_resultantForce = Vector3(0.0f, 0.0f, 0.0f);
	_prevPosition = _currPosition;
	_particleType = type;
}

void Particle::Update()
{
}

void Particle::DrawPoint()
{
	float color[3] = {
		_red, _green, _blue};
	float coord[3] = {
		_currPosition.x,
		_currPosition.y,
		_currPosition.z};

	Graphics::DrawPointParticles(
		1, _radius, coord, color);
}

void Particle::DrawSphere()
{
	float color[3] = {
		_red, _green, _blue};
	float coord[3] = {
		_currPosition.x,
		_currPosition.y,
		_currPosition.z};

	Graphics::DrawSphereParticles(
		1, _radius, coord, color);
}

void Particle::ResetForces()
{
	_resultantForce = Vector3(0.0f, 0.0f, 0.0f);
}

