// simulation.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"
#include "PhysicsSimulation/simulation.h"

Simulation::Simulation()
{
	_currPlane = 0;
	_currSpring = 0;
	_currParticle = 0;
	_currConstraint = 0;
	_currForceGenerator = 0;

	_dissipative = 0.5f;

	// Integrator is now an abstract base class and cannot be instantiated directly.
	// You must instantiate a concrete derived class, e.g., EulerIntegrator.
	// #include "PhysicsSimulation/euler_integrator.h" // Make sure to include the concrete integrator header
	// _integrator = new EulerIntegrator(); // Example instantiation

	// For better resource management, consider using a smart pointer:
	// std::unique_ptr<Integrator> integrator_; // In Simulation class definition
	// integrator_ = std::make_unique<EulerIntegrator>(); // In constructor

	// For now, let's initialize it to nullptr, assuming it will be set later
	// or via dependency injection. If a default is always needed, uncomment
	// and adapt the instantiation line above.
	_integrator = nullptr; // Or initialize with a default concrete integrator
}

void Simulation::AddCube(Cube* cube)
{
	float stiffness = 100.0f;
	float damping = 0.5f;

	// adiciona as particulas do cubo ao sistema
    for(int i = _currParticle; i < _currParticle + 8; i++)
	{
		_particles[i] = &cube->_particles[i - _currParticle];
	}
	_currParticle += 8;
	
	// cria as molas do cubo
    for(int j = 0; j < 7; j++)
	{
		for(int k = j; k < 8; k++)
		{
			AddSpring(stiffness, damping, &cube->_particles[j], &cube->_particles[k]);	
		}
	}
}

void Simulation::AddCloth(Cloth* cloth)
{
	float stiffness = 100.0f;
	float damping = 0.5f;

	// adiciona as particulas do pano ao sistema
	int j = cloth->_dimU * cloth->_dimV;
	for(int i = _currParticle; i < _currParticle + j; i++)
	{
		_particles[i] = &cloth->_particles[i - _currParticle];
	}
	_currParticle += j;

	// cria as molas do pano
	int nU = cloth->_dimU;
	int nV = cloth->_dimV;

	int lastRow = nU *(nV-1);

	Vector3 v;
	float length;

	int index = 0;
	for(int i = 0; i < nU-1; i++)
	{
		v = cloth->_particles[lastRow+i]._currPosition;
		v -= cloth->_particles[lastRow+i+1]._currPosition;
		length = v.Length();
		AddConstraint(length, &cloth->_particles[lastRow+i], &cloth->_particles[lastRow+i+1]);
		AddSpring(stiffness, damping, &cloth->_particles[lastRow+i], &cloth->_particles[lastRow+i+1]);
		for(int j = 0; j < nV-1; j++)
		{
			v = cloth->_particles[index]._currPosition;
			v -= cloth->_particles[index+1]._currPosition;
			length = v.Length();
			AddConstraint(length, &cloth->_particles[index], &cloth->_particles[index+1]);

			v = cloth->_particles[index]._currPosition;
			v -= cloth->_particles[index+nV]._currPosition;
			length = v.Length();
			AddConstraint(length, &cloth->_particles[index], &cloth->_particles[index+nV]);

			AddSpring(stiffness, damping, &cloth->_particles[index], &cloth->_particles[index+1]);
			AddSpring(stiffness, damping, &cloth->_particles[index], &cloth->_particles[index+nV]);
			AddSpring(stiffness, damping, &cloth->_particles[index], &cloth->_particles[index+nV+1]);
			AddSpring(stiffness, damping, &cloth->_particles[index+1], &cloth->_particles[index+nV]);
			index++;
		}
		v = cloth->_particles[index]._currPosition;
		v -= cloth->_particles[index+nV]._currPosition;
		length = v.Length();
		AddConstraint(length, &cloth->_particles[index], &cloth->_particles[index+nV]);
		AddSpring(stiffness, damping, &cloth->_particles[index], &cloth->_particles[index+nV]);
		index++;
	}

	index = 0;
	for(int i = 0; i < nU-2; i++)
	{
		AddSpring(stiffness, damping, &cloth->_particles[lastRow+i],   &cloth->_particles[lastRow+i+2]);
		for(int j = 0; j < nV-2; j++)
		{
			AddSpring(stiffness, damping, &cloth->_particles[index],   &cloth->_particles[index+2]);
			AddSpring(stiffness, damping, &cloth->_particles[index],   &cloth->_particles[index+nV+nV]);
			index++;
		}
		AddSpring(stiffness, damping, &cloth->_particles[index], &cloth->_particles[index+nV+nV]);
		index += 2;
	}
}

void Simulation::AddPlane(Plane* plane)
{
	_planes[_currPlane] = plane;
	_currPlane++;
}

void Simulation::AddParticle(Particle* particle)
{
	_particles[_currParticle] = particle;
	_currParticle++;
}

void Simulation::AddForceGenerator(ForceGenerator* forceGenerator)
{
	_forceGenerators[_currForceGenerator] = forceGenerator;
	_currForceGenerator++;
}

void Simulation::AddParticleGenerator(ParticleGenerator* particleGenerator)
{
	// adiciona as particulas do gerador ao sistema
	size_t particle_count = particleGenerator->GetParticleCount();
	// Ensure there's enough space in _particles (assuming it's a fixed-size array)
	// A more robust solution would use std::vector or check bounds here.
	for (size_t i = 0; i < particle_count; ++i)
	{
		// Get the address of the particle managed by the generator
		// Warning: Simulation now holds raw pointers to particles owned by ParticleGenerator.
		// This can lead to dangling pointers if the generator is destroyed or modifies its particles_.
		_particles[_currParticle + i] = &particleGenerator->GetParticle(i);
	}
	_currParticle += particle_count;
}

void Simulation::AddConstraint(float length, Particle* particleA, Particle* particleB)
{
	Constraint* constraint = new Constraint(length, particleA, particleB);
	_constraints[_currConstraint] = constraint;
	_currConstraint++;
}

void Simulation::AddSpring(float stiffness, float damping, Particle* particleA, Particle* particleB)
{
	Spring* spring = new Spring(stiffness, damping, particleA, particleB);
	_springs[_currSpring] = spring;
	_currSpring++;
}

void Simulation::UpdateSprings()
{
	// Particle p; // Removed unused particle
	for(int i = 0; i < _currSpring; i++)
	{
		_springs[i]->ApplyForce(); // ApplyForce takes no arguments
	}
}

void Simulation::UpdateConstraints()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < _currConstraint; j++)
		{
			_constraints[j]->SatisfyConstraint();
		}
	}
}

void Simulation::UpdateParticles()
{
	int i;
	for(i = 0; i < _currParticle; i++)
	{
		if(_particles[i]->_particleType == Particle::ParticleType::ACTIVE)
		{
			for(int j = 0; j < _currForceGenerator; j++)
			{
				_forceGenerators[j]->ApplyForce(*_particles[i]);
			}
		}
	}

	for(i = 0; i < _currParticle; i++)
	{
		if(_particles[i]->_particleType == Particle::ParticleType::ACTIVE)
		{
			float mass = _particles[i]->_mass;

			_acceleration.x = _particles[i]->_resultantForce.x / mass;
			_acceleration.y = _particles[i]->_resultantForce.y / mass;
			_acceleration.z = _particles[i]->_resultantForce.z / mass;

			// Integrate method now requires Particle& and dt.
			// Ensure _integrator is valid and dt is passed to this function.
			// TODO: Pass dt as an argument to Simulation::Update and Simulation::UpdateParticles.
			if (_integrator) { // Check if integrator exists
				_integrator->Integrate(_acceleration, *_particles[i], 0.05f); // Pass particle by reference and add dt
			} else {
				// Handle the case where no integrator is set (e.g., log an error)
			}
		}
	}

	for(i = 0; i < _currParticle; i++)
	{
		for(int j = 0; j < _currParticle; j++)
		{
			if(j != i)
			{
				Vector3 distance;
				distance.x = _particles[i]->_currPosition.x - _particles[j]->_currPosition.x;
				distance.y = _particles[i]->_currPosition.y - _particles[j]->_currPosition.y;
				distance.z = _particles[i]->_currPosition.z - _particles[j]->_currPosition.z;

				float h = _particles[i]->_radius + _particles[j]->_radius;

				if(distance.Length() < h)
				{
						float w = h - distance.Length();
						distance.Normalize();
						distance *= w / 2.0f;
						_particles[i]->_currPosition += distance;
						_particles[j]->_currPosition -= distance;

						Vector3 ta, tb;
						distance.Normalize();
						ta = tb = distance;

						ta *= Dot(_particles[i]->_currVelocity, distance);
						tb *= Dot(_particles[j]->_currVelocity, distance);

						ta *= 2.0f;
						tb *= 2.0f;
						
						_particles[i]->_currVelocity -= ta;
						_particles[j]->_currVelocity -= tb;

						_particles[i]->_currVelocity *= _dissipative;
						_particles[j]->_currVelocity *= _dissipative;
				}
			}
		}
	}

	for(i = 0; i < _currParticle; i++)
	{
		for(int j = 0; j < _currPlane; j++)
		{
			Vector3 planeNormal = _planes[j]->_normal;
			Vector3 planePosition = _planes[j]->_position;
			planeNormal.Normalize();

			float d = -(planePosition.x * planeNormal.x +
				planePosition.y * planeNormal.y +
				planePosition.z * planeNormal.z);

			float distance = _particles[i]->_currPosition.x * planeNormal.x +
				_particles[i]->_currPosition.y * planeNormal.y +
				_particles[i]->_currPosition.z * planeNormal.z + d;

			distance -= _particles[i]->_radius;

			if(distance < 0.0f)
			{
				planeNormal *= -distance;
				_particles[i]->_currPosition += planeNormal;

				Vector3 t;
				planeNormal.Normalize();
				t = planeNormal;

				t *= Dot(_particles[i]->_currVelocity, planeNormal);

				t *= 2.0f;
				
				_particles[i]->_currVelocity -= t;

				_particles[i]->_currVelocity *= _dissipative;
			}
		}
	}

	for(i = 0; i < _currParticle; i++)
	{
		if(_particles[i]->_particleType == Particle::ParticleType::ACTIVE)
            _particles[i]->ResetForces();
	}
}

void Simulation::UpdateParticleGenerator()
{
	_particleGenerator->Update();
}

void Simulation::Update()
{
	UpdateSprings();
	UpdateParticles();
	UpdateConstraints();
}

void Simulation::DrawPlanes()
{
	for(int i = 0; i < _currPlane; i++)
	{
		_planes[i]->Draw();
	}
}

void Simulation::DrawSprings()
{
	for(int i = 0; i < _currSpring; i++)
	{
		_springs[i]->Draw();
	}
}

void Simulation::DrawParticles()
{
	for(int i = 0; i < _currParticle; i++)
	{
		_particles[i]->DrawSphere();
	}
}

void Simulation::Draw()
{
	DrawPlanes();
	DrawSprings();
	DrawParticles();
}
