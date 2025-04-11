// main.cpp
// Simulação Física para Jogos
// W. Celes - celes@inf.puc-rio.br
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, 2009

#include <stdio.h>
#include <stdlib.h>

//#include <windows.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "PhysicsSimulation/graphics.h"
#include "PhysicsSimulation/gravity.h"
#include "PhysicsSimulation/medium.h"
#include "PhysicsSimulation/simulation.h"

Simulation* mySim = new Simulation();

static void Initialize()
{
	Particle::ParticleType passive = Particle::ParticleType::PASSIVE;
	Particle::ParticleType active = Particle::ParticleType::ACTIVE;

	//
	// Criando caixa a partir de planos
	//
	float size = 3.0f;

	float planeR = 0.5f;
	float planeG = 0.5f;
	float planeB = 0.5f;

	// Plane Bottom
	Vector3 normal0 = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 position0 = Vector3(0.0f, 0.0f, 0.0f);

	Plane* plane0 = new Plane();
	plane0->Initialize(size, normal0, position0, planeR, planeG, planeB);
	mySim->AddPlane(plane0);

	// Plane Right
	Vector3 normal1 = Vector3(-1.0f, 0.0f, 0.0f);
	Vector3 position1 = Vector3(size, size, 0.0f);

	Plane* plane1 = new Plane();
	plane1->Initialize(size, normal1, position1, planeR, planeG, planeB);
	mySim->AddPlane(plane1);

	// Plane Left
	Vector3 normal2 = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 position2 = Vector3(-size, size, 0.0f);

	Plane* plane2 = new Plane();
	plane2->Initialize(size, normal2, position2, planeR, planeG, planeB);
	mySim->AddPlane(plane2);

	// Plane Front
	Vector3 normal3 = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 position3 = Vector3(0.0f, size, size);

	Plane* plane3 = new Plane();
	plane3->Initialize(size, normal3, position3, planeR, planeG, planeB);
	mySim->AddPlane(plane3);

	// Plane Back
	Vector3 normal4 = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 position4 = Vector3(0.0f, size, -size);

	Plane* plane4 = new Plane();
	plane4->Initialize(size, normal4, position4, planeR, planeG, planeB);
	mySim->AddPlane(plane4);

	// Particle Generator
	float genMass = 10.0f;
	float genRadius = 0.5f;
	int genMax = 250;
	float genX = 0.0f;
	float genY = 25.0f;
	float genZ = 0.0f;

	ParticleGenerator* generator = new ParticleGenerator();
	generator->Initialize(genMass, genRadius, genMax, genX, genY, genZ);
	mySim->AddParticleGenerator(generator);

// 	// Particle
// 	float particleMass = 100.0f;
// 	float particleRadius = 2.5f;
// 	float particleX = 0.0f;
// 	float particleY = 2.5f;
// 	float particleZ = 0.0f;
// 	float particleR = 1.0f;
// 	float particleG = 0.0f;
// 	float particleB = 0.0f;
// 
// 	Particle* particle = new Particle();
// 	particle->Initialize(particleMass, particleRadius, particleX, particleY, particleZ, particleR, particleG, particleB, passive);
// 	mySim->AddParticle(particle);

// 	// Cube
// 	float cubeMass = 2.0f;
// 	float cubeRadius = 0.1f;
// 	float xMin = -2.0f;
// 	float xMax = +0.0f;
// 	float yMin = 13.0f;
// 	float yMax = 15.0f;
// 	float zMin = -1.0f;
// 	float zMax = +1.0f;
// 	float cubeR = 0.0f;
// 	float cubeG = 1.0f;
// 	float cubeB = 0.0f;
// 
// 	Cube* cube = new Cube();
// 	cube->Initialize(cubeMass, cubeRadius, xMin, xMax, yMin, yMax, zMin, zMax, cubeR, cubeG, cubeB, active);
// 	mySim->AddCube(cube);

// 	// Cloth
// 	float clothMass = 100.0f;
// 	float clothRadius = 0.1f;
// 	int nU = 15;
// 	int nV = 15;
// 	Vector3 p = Vector3(3.0f, 15.0f, 3.0f);
// 	Vector3 pU = Vector3(-3.0f, 15.0f, 3.0f);
// 	Vector3 pV = Vector3(3.0f, 15.0f, -3.0f);
// 	float clothR = 0.0f;
// 	float clothG = 0.0f;
// 	float clothB = 1.0f;
// 
// 	Cloth* cloth = new Cloth();
// 	cloth->Initialize(clothMass, clothRadius, nU, nV, p, pU, pV, clothR, clothG, clothB, active);
// 	mySim->AddCloth(cloth);

	Gravity* gravity = new Gravity();
	mySim->AddForceGenerator((ForceGenerator*)gravity);

	/*Medium* air = new Medium(0.50f);
	mySim->AddForceGenerator((ForceGenerator*)air);*/

	Euler* integrator = new Euler();
	mySim->_integrator = (Integrator*)integrator;

	/*Verlet* integrator = new Verlet();
	mySim->_integrator = (Integrator*)integrator;*/
}

static void Update()
{
	//for(int i = 0; i < 10; i++)
		mySim->Update();
}

static void Draw()
{
	Graphics::BeginDrawing();

	Graphics::LoadCamera(
		60.0f,               // angulo de abertura da camera
		-12.5f, 7.5f, 20.0f,   // posicao da camera
		0.0f, 5.0f, 0.0f,    // centro da cena
		0.0f, 1.0f, 0.0f     // vetor "up"
	);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(6.0f);
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
	glTranslatef(0.0f, -3.0f, 0.0f);
	mySim->Draw();
	glPopAttrib();

	Graphics::EndDrawing();
}

// Callback de evento do teclado
static void Keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
	}
}

// Callback de evento do teclado
static void Keyboard (int key, int x, int y)
{
	float move = 1.0f;

	switch (key) {
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
	}
}

// Callback de idle: simula e redesenha
static void Idle ()
{
	Update();
	Draw();
}

// Função principal: inicializa Glut e registra callbacks
int main (int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(1280,768);
	glutCreateWindow("Simulacao Fisica");
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Keyboard);
	glutIdleFunc(Idle);

	Initialize();

	glutMainLoop();
	
	return 0;
}
