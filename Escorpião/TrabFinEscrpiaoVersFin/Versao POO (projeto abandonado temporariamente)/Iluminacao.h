/*Iluminacao.h*/
/*Classe utilizada para os elementos de iluminação do mundo */
#pragma once
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#include "Cameras.h"
#include "Escorpiao.h"
#include "Iluminacao.h"
#include "DesenhaPrimitivas.h"
#include "Constantes.h"
#include "Testes.h"
using namespace std;
using namespace nsConstantes;

class Iluminacao
{
public:
	Iluminacao();
	~Iluminacao();
	//Variáveis públicas
	bool texturaSimNao;
	GLfloat posicaoLuz0[4] = { 0.0f, 0.0f, 25.0f, 0.0 };
	GLfloat luzAmbiente0[4] = { 0.19, 0.19, 0.19, 0.0 };
	GLfloat luzDifusa0[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat especularidade0[4] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat posicaoLuz1[4] = { 0.0f, 6.0f, 12.0f, 0.0 };
	GLfloat luzAmbiente1[4] = { 0.3, 0.3, 0.3, 0.0 };
	GLfloat luzDifusa1[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat especularidade1[4] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat especMaterialTexture0;
	GLfloat especMaterialTexture1;
	GLfloat especMaterialNoTexture;
};
