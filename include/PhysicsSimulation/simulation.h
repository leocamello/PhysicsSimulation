// simulation.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef SIMULATION_H
#define SIMULATION_H

#include "cube.h"
#include "cloth.h"
#include "euler.h"
#include "plane.h"
#include "spring.h"
#include "verlet.h"
#include "particle.h"
#include "integrator.h"
#include "constraint.h"
#include "forcegenerator.h"
#include "particlegenerator.h"

class Simulation
{
public:
	Simulation();
	
	int _currPlane;
	int _currSpring;
	int _currParticle;
	int _currConstraint;
	int _currForceGenerator;

	float _dissipative;
	
	Vector3 _acceleration;

	Plane* _planes[10];
	Spring* _springs[1024];
	Particle* _particles[1024];
	Constraint* _constraints[1024];
	ForceGenerator* _forceGenerators[5];
	ParticleGenerator* _particleGenerator;

	Integrator* _integrator;

	void Update();
	void Draw();

	void AddCube(Cube* cube);
	void AddCloth(Cloth* cloth);
	void AddPlane(Plane* plane);
	void AddParticle(Particle* particle);
	void AddForceGenerator(ForceGenerator* forceGenerator);
	void AddParticleGenerator(ParticleGenerator* particleGenerator);
	void AddConstraint(float length, Particle* particleA, Particle* particleB);
	void AddSpring(float stiffness, float damping, Particle* particleA, Particle* particleB);

	void UpdateSprings();
	void UpdateParticles();
	void UpdateConstraints();
	void UpdateParticleGenerator();

	void DrawPlanes();
	void DrawSprings();
	void DrawParticles();
};

#endif