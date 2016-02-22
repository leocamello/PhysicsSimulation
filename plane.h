// plane.h
// Simulação Física para Jogos
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

class Plane
{
public:
	Plane();
	~Plane();

	float _size;
	Vector3 _normal;
	Vector3 _position;
	float _red, _green, _blue, _alpha;

	void Initialize(
		float size, 
		Vector3 normal, 
		Vector3 position, 
		float r, float g, float b);
	void Update();
	void Draw();
};

#endif