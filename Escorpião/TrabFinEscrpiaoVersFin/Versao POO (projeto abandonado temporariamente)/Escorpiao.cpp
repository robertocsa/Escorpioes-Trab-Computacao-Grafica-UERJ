/* Escorpiao.cpp
Classe Escorpião
Desenha os escorpiões
*/
#pragma once

#include "Constantes.h"
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

/*////////////////////////////////////////////////////////////////////////*/
/* Classe Escorpiao */
Escorpiao::Escorpiao() {
	this->inicializaIluminacao();
	this->inicializaRenderizacao();
	this->desenhaEscorpiao();
}
Escorpiao::Escorpiao(int idEscorpiao) {
	this->idEscorpiao = idEscorpiao;
	this->inicializaIluminacao();
	this->inicializaRenderizacao();
	this->desenhaEscorpiao();
}
int Escorpiao::obtemIdEscorpiao(void)
{
	return this->idEscorpiao;
}
void Escorpiao::inicializaRenderizacao(void) { 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	_textIdQuelicera = loadTexture(nomeArqTextQuelicera);
	_textIdPele = loadTexture(nomeArqTextPele);
	_textIdPata = loadTexture(nomeArqTextPata);
}
//Inicializa a iluminação (LIGHT0)
void Escorpiao::inicializaIluminacao(void)
{
	Iluminacao iluminacao = Iluminacao();
}
// Insere a imagem em uma textura e retorna o id da textura
GLuint Escorpiao::loadTexture(char *filename) {
	
	GLuint textureId;
	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
												//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,	//Always GL_TEXTURE_2D
		0,						//0 for now
		GL_RGB,					//Format OpenGL uses for image
		theTexMap.GetNumCols(),	//Width 
		theTexMap.GetNumRows(),	//Height
		0,						//The border of the image
		GL_RGB,					//GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,		//GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
		theTexMap.ImageData());	//The actual pixel data
	return textureId; //Returns the id of the texture
}

void Escorpiao::desenhaPata(void) {
	glBindTexture(GL_TEXTURE_2D, _textIdPata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glRotatef(angGarraDirY + 60, 0.0f, 1.0f, 0.0f);

	desenhaCilindro(diametroCilindro / 3, tamPata);
	glTranslatef(0.0f, 0.0f, tamPata + diametroEsfera / 15);

	glTranslatef(0.0f, 0.0f, diametroEsfera / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	desenhaCilindro(diametroCilindro / 3, tamPata);
	glTranslatef(0.0f, 0.0f, tamPata + diametroEsfera / 15);
	
	glTranslatef(0.0f, 0.0f, diametroEsfera / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);
	desenhaCone(diametroCilindro / 3, tamPata);
}
//Realiza o desenho do escorpiao
void Escorpiao::desenhaEscorpiao() {
	_pos posicao;
	posicao.x = 0.0;
	posicao.y = 0.0;
	posicao.z = 0.0;
	desenhaEscorpiao(posicao);
}
//Realiza o desenho do escorpiao
void Escorpiao::desenhaEscorpiao(_pos posicao) {
	glBindTexture(GL_TEXTURE_2D, _textIdPele);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPushMatrix();
	glTranslatef(posicao.x, posicao.y, posicao.z);	
	//Desenha extensão da boca:
	desenhaElipsoide(95.0, 115.0, 0.07, 0.55, 0.05); 
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textIdQuelicera);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTranslatef(0.0, 1.43, 0.0);
	//Desenha quelíceras:
	glTranslatef(abertQuelicera, -0.045, -0.04);	
	desenhaQuelicera();
    //desenhaElipsoide(0.0, 180.0, 0.015, 0.02, 0.072);
	glTranslatef(-2 * abertQuelicera, 0.0, 0.0);
	desenhaQuelicera();
	//desenhaElipsoide(0.0, 180.0, 0.015, 0.02, 0.072);		
	glPopMatrix();
	glTranslatef(0.0, -0.37, 0.0);	
	//Desenha olhos:
	desenhaOlhos();	
	glTranslatef(0.0, 0.37, 0.0);
	//Desenha cabeça:	
	glBindTexture(GL_TEXTURE_2D, _textIdPele);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glRotatef(-angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(0.0, 20.0, 0.32, 1.4, 0.27);		
	//glColor3f(1.0, 0, 0);
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(-angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(18.0, 29.0, 0.31, 1.2, 0.26);
	glRotatef(-angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(27.0, 38.0, 0.30, 1.2, 0.25);	
	glRotatef(-angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(36.0, 47.0, 0.29, 1.2, 0.24);
	glRotatef(-angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(45.0, 58.0, 0.28, 1.2, 0.23);	
	glPushMatrix();
	//glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0, 1.1, 0.0);
	glRotatef(angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	desenhaElipsoide(118.0, 125.0, 0.27, 1.0, 0.22);
	glRotatef(angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, -0.14, 0.0);
	desenhaElipsoide(123.0, 150.0, 0.26, 0.75, 0.21);
	glRotatef(angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, -0.21, 0.0);
	desenhaElipsoide(148.0, 180.0, 0.25, 0.5, 0.20);
	glRotatef(angCurvaCorpo, 1.0f, 0.0f, 0.0f);
	glPopMatrix();
	desenhaCauda();	
}
void Escorpiao::desenhaOlhos(void)
{	
	glPushMatrix();
	glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 1.7, 0.065);
	desenhaEsfera(0.04);
	glTranslatef(-0.10, 0.0, 0.0);
	desenhaEsfera(0.04);	
	glPopAttrib();
	glPopMatrix();
}
void Escorpiao::desenhaCauda(void)
{	
	glTranslatef(0.0, 0.26, 0.0);
	//rotação vertical da cauda:
	glRotatef(angVertCauda-20,1.0,0.0,0.0);
	//rotação horizontal da cauda:
	glRotatef(angHorzCauda, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.13, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.20, 0.08);
	//Segunda parte da cauda
	glTranslatef(0.0, -0.18, 0.0);
	glRotatef(angVertCauda/2-25, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.18, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.20, 0.08);
	//Terceira parte da cauda
	glTranslatef(0.0, -0.18, 0.0);
	glRotatef(angVertCauda/3-45, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.18, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.20, 0.08);
	//Quarta parte da cauda
	glTranslatef(0.0, -0.18, 0.0);
	glRotatef(angVertCauda/4 -50, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.18, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.20, 0.08);
	//Quinta parte da cauda
	glTranslatef(0.0, -0.18, 0.0);
	glRotatef(angVertCauda/5-60, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.18, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.20, 0.08);
	//Ferrão da cauda
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(angVertCauda / 5 - 60, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.1, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.06, 0.12, 0.08);	
	glPushMatrix();
	glRotatef(180, 0.00f, 1.00f, 0.00f);
	glRotatef(200, 1.00f, 0.00f, 0.00f);
	glTranslatef(0.0, 0.04, -0.12);
	desenhaQuelicera();
	glPopMatrix();
	//desenhaConeCurvado(0.00, PI / 6, 0.00, 2 * PI, 7.00, 2.00, 0.3);
}
void Escorpiao::alteraPosicao(_pos _posicao) {
	this->posicao = _posicao;
}
_pos Escorpiao::obtemPosicao(_pos _posicao) {
	return this->posicao;
}
void Escorpiao::atualizaMovimentosAutomaticos(void) {
	
	//Atualiza o movimento das quelíceras
	if (abrindoQuelicera) {
		if (abertQuelicera < 0.045) {
			abertQuelicera += 0.0017;
			escalaYQuel += 0.0001;
		} else {
			abrindoQuelicera = false;
		}
	}
	else {
		if (abertQuelicera > 0.022) {
			abertQuelicera -= 0.0017;
			escalaYQuel -= 0.0001;
		}
		else {
			abrindoQuelicera = true;
		}
	}
	//Atualiza o movimento do corpo
	if (curvandoCorpo) {
		if (angCurvaCorpo < 0.3) {
			angCurvaCorpo += 0.001;
		}
		else {
			curvandoCorpo = false;
		}
	}
	else {
		if (angCurvaCorpo > -0.3) {
			angCurvaCorpo -= 0.001;
		}
		else {
			curvandoCorpo = true;
		}
	}	
}