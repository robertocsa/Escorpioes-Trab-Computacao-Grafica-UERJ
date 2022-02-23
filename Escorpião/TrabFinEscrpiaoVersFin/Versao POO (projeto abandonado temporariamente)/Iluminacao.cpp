/*Iluminacao.cpp*/
/*Classe utilizada para os elementos de iluminação do mundo */
#include "Iluminacao.h"

Iluminacao::Iluminacao()
{
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente1);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);

	// Define os parâmetros da luz de número 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

	// Materials will follow current color
	glEnable(GL_COLOR_MATERIAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

	// Inicializa cores e parâmetros	
	glMateriali(GL_FRONT, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade0);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture0);
	glColor3f(0.5f, 0.6f, 0.8f);

	if (texturaSimNao) {
		glColor3f(0.9f, 0.9f, 0.9f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade1);
		glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture1);
	}
	else {
		glColor3f(0.8f, 0.9f, 1.0f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade1);
		glMateriali(GL_FRONT, GL_SHININESS, especMaterialNoTexture);
	}
}

Iluminacao::~Iluminacao()
{
	cout << "Objeto da classe iluminação encerrado" << endl;
}
