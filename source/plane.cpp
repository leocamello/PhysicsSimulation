// particle.cpp
// Simula��o F�sica para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#include "PhysicsSimulation/graphics.h"

#include "PhysicsSimulation/vector.h"
#include "PhysicsSimulation/plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::Initialize(
		float size, 
		Vector3 normal, 
		Vector3 position, 
		float r, float g, float b)
{
	_red = r;
	_green = g;
	_blue = b;
	_size = size;
	_normal = normal;
	_position = position;
}

void Plane::Update()
{
}

void Plane::Draw()
{
	Graphics::DrawPlane(
			_position.x,
			_position.y,
			_position.z,
			_normal.x,
			_normal.y,
			_normal.z,
			_size, _red, _green, _blue);
}
