// graphics.cpp
// Simulação Física para Jogos
// W. Celes - celes@inf.puc-rio.br
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, 2009

#include <stdlib.h>

//#include <windows.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "PhysicsSimulation/graphics.h"
#include "PhysicsSimulation/manipulator.h"
#include "PhysicsSimulation/vector.h"

void Graphics::BeginDrawing ()
{
	static bool first = true;
	if (first) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		first = false;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::EndDrawing ()
{
	glutSwapBuffers();
}

void Graphics::LoadCamera 
(float angle, 
 float x, float y, float z, 
 float cx, float cy, float cz, 
 float ux, float uy, float uz
 )
{
	Vector3 eye(x, y, z);
	Vector3 dir(cx, cy, cz);
	dir -= eye;
	int vp[4];
	glGetIntegerv(GL_VIEWPORT,vp);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,(float)vp[2]/vp[3],0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float inf[4] = {0.0f,0.0f,1.0f,0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, inf);
	// Camera manipulator
	Manipulator* manip = Manipulator::Instance();
	manip->SetZCenter(dir.Length());
	manip->Load();
	gluLookAt(x, y, z, cx, cy, cz, ux, uy, uz);
}

void Graphics::DrawPlane 
(float x, float y, float z, float nx, float ny, float nz,
 float size,
 float r, float g, float b
 )
{
	Vector3 n(nx, ny, nz); n.Normalize();
	Vector3 u(0.0f, 1.0f, 0.0f);
	Vector3 v = Cross(u, n);
	float angle = v.Length() * 90.0f;
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, v.x, v.y, v.z);
	glBegin(GL_QUADS);
	glNormal3f(0.0f,1.0f,0.0f);
	glVertex3f(-size,0.0f,-size);
	glVertex3f(-size,0.0f, size);
	glVertex3f( size,0.0f, size);
	glVertex3f( size,0.0f,-size);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

void Graphics::DrawSphere 
(float radius, float x, float y, float z, float r, float g, float b)
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(radius,32,32);
	glPopMatrix();
	glPopAttrib();
}

void Graphics::DrawSphereParticles 
(int n, float radius, float* coord, float* color)
{
	glPushAttrib(GL_CURRENT_BIT);
	for (int i=0; i<n; ++i) {
		glColor3fv(color+3*i);
		glPushMatrix();
		glTranslatef(coord[3*i+0], coord[3*i+1], coord[3*i+2]);
		glutSolidSphere(radius, 16, 16);
		glPopMatrix();
	}
	glPopAttrib();
}

void Graphics::DrawPointParticles 
(int n, float size, float* coord, float* color)
{
	glPushAttrib(GL_POINT_BIT);
	glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
	glPointSize(size);
	glEnable(GL_POINT_SMOOTH);
	glVertexPointer(3,GL_FLOAT,0,coord);
	glColorPointer(3,GL_FLOAT,0,color);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS,0,n);
	glPopClientAttrib();
	glPopAttrib();
}

void Graphics::DrawSpring 
(float width, float lrest, float *coord1, float* coord2)
{
	glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT);
	float l = sqrt(
		(coord1[0]-coord2[0]) * (coord1[0]-coord2[0]) +
		(coord1[1]-coord2[1]) * (coord1[1]-coord2[1]) +
		(coord1[2]-coord2[2]) * (coord1[2]-coord2[2]) 
		);
	if (l < lrest) {
		float t = 2*(lrest - l) / lrest;
		glColor3f(0.0f,0.0f,t);
	}
	else {
		float t = 2*(l - lrest) / lrest;
		glColor3f(t,0.0f,0.0f);
	}
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex3fv(coord1);
	glVertex3fv(coord2);
	glEnd();
	glPopAttrib();
}

void Graphics::DrawQuads 
(int n, unsigned int* ind, float* coord, float r, float g, float b)
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	for (int i=0; i<n; i+=4) {
		Vector3 a(coord[3*ind[i+0]+0]-coord[3*ind[i+2]+0],
			coord[3*ind[i+0]+1]-coord[3*ind[i+2]+1],
			coord[3*ind[i+0]+2]-coord[3*ind[i+2]+2]
			);
			Vector3 b(coord[3*ind[i+1]+0]-coord[3*ind[i+3]+0],
				coord[3*ind[i+1]+1]-coord[3*ind[i+3]+1],
				coord[3*ind[i+1]+2]-coord[3*ind[i+3]+2]
				);
				Vector3 n = Cross(a, b);
				glNormal3fv(&n.x);
				glVertex3fv(coord+3*(ind[i+0]));
				glVertex3fv(coord+3*(ind[i+1]));
				glVertex3fv(coord+3*(ind[i+2]));
				glVertex3fv(coord+3*(ind[i+3]));
	}
	glEnd();
	glPopAttrib();
}

void Graphics::DrawTriangles 
(int n, unsigned int* ind, float* coord, float r, float g, float b)
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<n; i+=3) {
		Vector3 a(coord[3*ind[i+1]+0]-coord[3*ind[i+0]+0],
			coord[3*ind[i+1]+1]-coord[3*ind[i+0]+1],
			coord[3*ind[i+1]+2]-coord[3*ind[i+0]+2]
			);
			Vector3 b(coord[3*ind[i+2]+0]-coord[3*ind[i+0]+0],
				coord[3*ind[i+2]+1]-coord[3*ind[i+0]+1],
				coord[3*ind[i+2]+2]-coord[3*ind[i+0]+2]
				);
				Vector3 n = Cross(a, b);
				glNormal3fv(&n.x);
				glVertex3fv(coord+3*(ind[i+0]));
				glVertex3fv(coord+3*(ind[i+1]));
				glVertex3fv(coord+3*(ind[i+2]));
	}
	glEnd();
	glPopAttrib();
}
