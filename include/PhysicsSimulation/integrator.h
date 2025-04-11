// integrator.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

struct Vector3;
class Particle;

class Integrator
{
public:
	Integrator();
	
    virtual void Integrate(Vector3 acceleration, Particle* particle);

protected:
	float _fixedTimeStep;

private:
};

#endif