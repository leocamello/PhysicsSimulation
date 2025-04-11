// cloth.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"
#include "PhysicsSimulation/cloth.h"

Cloth::Cloth()
{
}

Cloth::~Cloth()
{
}

void Cloth::Initialize(
		float mass, float radius,
		int nU, int nV,
		Vector3 p, Vector3 pU, Vector3 pV,		
		float r, float g, float b,
		Particle::ParticleType type)
{
	_dimU = nU;
	_dimV = nV;
	_mass = mass/(_dimU*_dimV);
	_radius = radius;
	_particles = new Particle[nU*nV];
	_particleType = type;

	_faces = (_dimU - 1) * (_dimV -1) * 4;

	Vector3 dU, dV;
	dU = pU;
	dV = pV;
	dU -= p;
	dV -= p;
	dU /= (float)(nU -1);
	dV /= (float)(nV -1);

	int index = 0;
	for(int i = 0; i < nU; i++)
	{
		for(int j = 0; j < nV; j++)
		{
			_particles[index].Initialize(
				_mass, _radius, 
				p.x + i*dU.x + j*dV.x, 
				p.y + i*dU.y + j*dV.y, 
				p.z + i*dU.z + j*dV.z, 
				r, g, b, _particleType);

			index++;
		}
	}
}

void Cloth::Update()
{
}

void Cloth::Draw()
{
	float* coord = new float[96];
	for(int i = 0; i < _dimU*_dimV; i++)
	{
		coord[i*3+0] = _particles[i]._currPosition.x; 
		coord[i*3+1] = _particles[i]._currPosition.y; 
		coord[i*3+2] = _particles[i]._currPosition.z;
	}

	unsigned int* quads1 = new unsigned int[48]; 
	unsigned int* quads2 = new unsigned int[48]; 
	
	int index = 0;
	int textureIndex1 = 0;
	int textureIndex2 = 0;
	for(int i = 0; i < _dimU-1; i++)
	{
		for(int j = 0; j < _dimV-1; j++)
		{
			if( index % 2 == 0)
			{
				quads1[textureIndex1+0] = index;
				quads1[textureIndex1+1] = index+1;
				quads1[textureIndex1+2] = index+_dimV+1;
				quads1[textureIndex1+3] = index+_dimV;
				textureIndex1 += 4;
			}
			else
			{
				quads2[textureIndex2+0] = index;
				quads2[textureIndex2+1] = index+1;
				quads2[textureIndex2+2] = index+_dimV+1;
				quads2[textureIndex2+3] = index+_dimV;
				textureIndex2 += 4;  
			}
			index++;
		}
		index++;
	} 

	Graphics::DrawQuads(textureIndex1, quads1, coord, _red, _green, _blue);
	Graphics::DrawQuads(textureIndex2, quads2, coord, 1.0f - _red, 1.0f - _green, 1.0f - _blue);
}