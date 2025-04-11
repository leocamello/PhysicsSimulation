// forcegenerator.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Particle;

class ForceGenerator
{
public:
	ForceGenerator();
	virtual ~ForceGenerator();
	virtual void ApplyForce(Particle* particle);
};

#endif