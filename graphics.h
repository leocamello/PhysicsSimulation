// graphics.h
// Simulação Física para Jogos
// W. Celes - celes@inf.puc-rio.br
// L. Camello - camello@tecgraf.puc-rio.br
// PUC-Rio, 2009

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
public:
	// Inicializa desenho de quadro
	static void BeginDrawing ();

	// Finaliza desenho de quadro
	static void EndDrawing ();

	// Carrega camera para visualizar cena
	// angle: angulo de abertura da camera
	// x, y, z: posicao da camera
	// cx, cy, cz: posicao do centro da cena
	// ux, uy, uz: vetor "up" da camera
	static void LoadCamera 
		(float angle, 
		float x, float y, float z, 
		float cx, float cy, float cz, 
		float ux, float uy, float uz
		);

	// Desenha um plano na cena
	// x, y, z: ponto no plano 
	// nx, ny, nz: normal do plano
	// size: extensão do desenho do plano
	// r, g, b: cor para desenhar o plano
	static void DrawPlane 
		(float x, float y, float z, float nx, float ny, float nz,
		float size,
		float r, float g, float b
		);

	// Desenha uma esfera na cena
	// radius: raio da esfera
	// x, y, z: posição do centro da esfera
	// r, g, b: cor para desenhar a esfera
	static void DrawSphere 
		(float radius, float x, float y, float z, float r, float g, float b);

	// Desenha partículas como pequenas esferas
	// n: número de partículas
	// radius: raio para desenho das partículas
	// coord: vetor de coordenadas das posicoes das partículas
	//       x0 y0 z0 x1 y1 z1 x2 y2 z2 ...
	// color: vetor de cores das partículas
	//       r0 g0 b0 r1 g1 b1 r2 g2 b2 ...
	static void DrawSphereParticles 
		(int n, float radius, float* coord, float* color);

	// Desenha partículas como pontos
	// n: número de partículas
	// size: tamanho, em pixels, para desenho das partículas
	// coord: vetor de coordenadas das posicoes das partículas
	//       x0 y0 z0 x1 y1 z1 x2 y2 z2 ...
	// color: vetor de cores das partículas
	//       r0 g0 b0 r1 g1 b1 r2 g2 b2 ...
	static void DrawPointParticles 
		(int n, float size, float* coord, float* color);

	// Desenha mola. A mola é desenhada em preto quanto em repouso, variando
	// para o vermelho quando estendida e azul quando comprimida.
	// width: largura, em pixels, da linha que representa a mola
	// lrest: comprimento de repouso
	// coord1: vetor (x, y, z) de uma extremidade
	// coord2: vetor (x, y, z) da outra extremidade
	static void DrawSpring 
		(float width, float lrest, float *coord1, float* coord2);

	// Desenha quadriláteos na cena
	// n: números de pontos que definem os quadriláteros (n = 4*nquad)
	// ind: vetor, com dimensão n, com os índices dos vertices dos quads
	//       v0 v1 v2 v3 v0 v1 v2 v3 v0 v1 v2 v3 ...
	// r, g, b: cor de desenho dos quadriláteros
	static void DrawQuads 
		(int n, unsigned int* ind, float* coord, float r, float g, float b);

	// Desenha triângulos na cena
	// n: números de pontos que definem os triângulos (n = 3*ntri)
	// ind: vetor, com dimensão n, com os índices dos vertices dos triângulos
	//       v0 v1 v2 v0 v1 v2 v0 v1 v2 ...
	// r, g, b: cor de desenho dos quadriláteros
	static void DrawTriangles 
		(int n, unsigned int* ind, float* coord, float r, float g, float b);

	static void DrawLine
		(float x1, float y1, float z1, float x2, float y2, float z2);

};
#endif
