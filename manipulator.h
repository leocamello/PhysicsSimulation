// manipulator.h
// Simulação Física para Jogos
// W. Celes - celes@inf.puc-rio.br
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, Set 2009

#ifndef MANIPULATOR_H
#define MANIPULATOR_H

class Manipulator
{
	static Manipulator* s_instance;
public:
	static Manipulator* Instance ();
	void SetZCenter (float zcenter);
	void Load ();
	void Identity();
	void Rotate (float angle, float rx, float ry, float rz);
	void Scale (float sx, float sy, float sz);

private:
	Manipulator ();

private:
	float m_matrix[16];
	float m_zcenter;
};

#endif
