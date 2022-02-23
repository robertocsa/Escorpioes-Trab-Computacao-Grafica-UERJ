/* Principal.cpp */
/*Classe Principal do projeto 
Este arquivo contém a função 'main'. 
A execução do programa começa e termina em main.
*/

/* Principal.h */
/*Classe Principal do projeto */
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

	void inicializaClasse(void);
	int obtemIdEscorpiaoEmFoco(void);
	int obtemIdLuzEmFoco(void);
	int obtemIdCameraEmFoco(void);
	Escorpiao obtemObjEscorpiaoEmFoco(void);
	Iluminacao obtemObjLuzEmFoco(void);
	Camera obtemObjCameraEmFoco(void);
	void alteraEscorpiaoEmFoco(void);
	void alteraCameraEmFoco(void);
	void alteraLuzEmFoco(void);
	//void atualizaMovimentosAutomaticos(void);
	//void handleResize(int w, int h);
	//void gerenciaMouse(int botao, int estado, int x, int y);
	//void tecladoFuncoesEspeciais(int tecla, int x, int y);
	//void teclado(unsigned char tecla, int x, int y);
	void inicializaRenderizacao(void);
	GLuint loadTexture(char * filename);
	void inicializaIluminacao(void);
	//void desenhaCena(void);
	void desenhaCeu(float deltaHorz, float deltaVert, float raio);
	void desenhaEscorpiao(void);
	void desenhaPiso(float raio);
	void desenhaSetasOrientacao(void);
	int idEscorpiaoEmFoco;
	int idLuzEmFoco;
	int idCameraEmFoco;
	Escorpiao objEscorpiaoEmFoco;
	Iluminacao objIluminacaoEmFoco;
	Camera objCameraEmFoco;
	GLuint _textIdCeu;
	GLuint _textIdPiso;
	bool texturaSimNao;
	GLUquadric *quadCeu;

void inicializaClasse(void) {
	objCameraEmFoco = Camera();
}
int obtemIdEscorpiaoEmFoco(void)
{
	return idEscorpiaoEmFoco;
}
int obtemIdLuzEmFoco(void)
{
	return idLuzEmFoco;
}
int obtemIdCameraEmFoco(void)
{
	return idCameraEmFoco;
}
Escorpiao obtemObjEscorpiaoEmFoco(void)
{
	return objEscorpiaoEmFoco;
}
Iluminacao obtemObjLuzEmFoco(void)
{
	return objIluminacaoEmFoco;
}
Camera obtemObjCameraEmFoco(void)
{
	return objCameraEmFoco;
}
void alteraEscorpiaoEmFoco(void)
{
	idEscorpiaoEmFoco = obtemIdEscorpiaoEmFoco() + 1;
	Escorpioes::alteraEscorpiaoAtivo(idEscorpiaoEmFoco);
	if (idEscorpiaoEmFoco == NUM_ESCORPIOES + 1) {
		idEscorpiaoEmFoco = 1;
	}
}
void alteraCameraEmFoco(void)
{
	idCameraEmFoco = obtemIdCameraEmFoco() + 1;
	Cameras::alteraCameraAtiva(idCameraEmFoco);
	if (idCameraEmFoco == NUM_CAMERAS + 1) {
		idCameraEmFoco = 1;
	}
}
void alteraLuzEmFoco(void)
{
	idLuzEmFoco = obtemIdLuzEmFoco() + 1;
	if (idLuzEmFoco == NUM_LUZES + 1) {
		idLuzEmFoco = 1;
	}
}
void atualizaMovimentosAutomaticos(void) {
}
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 0.2, 80.0);
}
// Função callback chamada para gerenciar eventos do mouse
void gerenciaMouse(int botao, int estado, int x, int y)
{
	_camera objAtribCamera = objCameraEmFoco.obtemAtributos();
	if (botao == GLUT_LEFT_BUTTON)
		if (estado == GLUT_DOWN) {  // Zoom-out
			if (objAtribCamera.distOlhar < 82) {
				objAtribCamera.distOlhar += 1.5;
			}
		}
	if (botao == GLUT_RIGHT_BUTTON)
		if (estado == GLUT_DOWN) {  // Zoom-out
			if (objAtribCamera.distOlhar > 0) {
				objAtribCamera.distOlhar -= 1.5;
			}
			glutPostRedisplay();
		}
}
//Função callback chamada para gerenciar os eventos de teclas de função especial do teclado
void tecladoFuncoesEspeciais(int tecla, int x, int y) {
	int teclasFuncao = glutGetModifiers();
	//cout << teclasFuncao << endl;
	_camera objAtribCamera = objCameraEmFoco.obtemAtributos();
	if (teclasFuncao == 0.00) {
		switch (tecla) {
		case GLUT_KEY_RIGHT:	//Aumenta o ângulo de visão no eixo Z		
			objAtribCamera.angVisao.z += 1.5;
			break;
		case GLUT_KEY_LEFT: //Reduz o ângulo de visão no eixo Z
			objAtribCamera.angVisao.z -= 1.5;
			break;
		case GLUT_KEY_UP:  //Aumenta o ângulo de visão no eixo X
			objAtribCamera.angVisao.x += 1.5;
			break;
		case GLUT_KEY_DOWN: //Reduz o ângulo de visão no eixo X
			objAtribCamera.angVisao.x -= 1.5;
			break;
		case GLUT_KEY_PAGE_UP: 	//Aumenta a distância do olhar:
			objAtribCamera.distOlhar += 1.5;
			break;
		case GLUT_KEY_PAGE_DOWN: //Reduz a distância do olhar:
			objAtribCamera.distOlhar -= 1.5;
			break;
		default:
			break;
		}
		objCameraEmFoco.alteraAtributos(objAtribCamera);
	}
	/*
	else {
		if (teclasFuncao == GLUT_ACTIVE_CTRL) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				xOlhar += 1.5;
				break;
			case GLUT_KEY_LEFT:
				yOlhar += 1.5;
				break;
			case GLUT_KEY_UP:
				zOlhar += 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == GLUT_ACTIVE_ALT) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				xcOlhar += 1.5;
				break;
			case GLUT_KEY_LEFT:
				ycOlhar += 1.5;
				break;
			case GLUT_KEY_UP:
				zcOlhar += 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == GLUT_ACTIVE_CTRL | GLUT_ACTIVE_SHIFT ) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				xOlhar -= 1.5;
				break;
			case GLUT_KEY_LEFT:
				yOlhar -= 1.5;
				break;
			case GLUT_KEY_UP:
				zOlhar -= 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == GLUT_ACTIVE_ALT | GLUT_ACTIVE_SHIFT) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				xcOlhar -= 1.5;
				break;
			case GLUT_KEY_LEFT:
				ycOlhar -= 1.5;
				break;
			case GLUT_KEY_UP:
				zcOlhar -= 1.5;
				break;
			default:
				break;
			}
		}
}*/
	glutPostRedisplay();
}
//Função callback chamada para gerenciar os eventos de teclado
void teclado(unsigned char tecla, int x, int y) {
	int teclasFuncao = glutGetModifiers();
	switch (tecla) {
	case 27: //tecla escape (saída do aplicativo)
		exit(0);
		/*  Configurações dos ângulos da pata:
	case '1': //Increase arm angle
		angPata1No += 3;
		if (angPata1No >= 360) angPata1No = 0;
		glutPostRedisplay();
		break;
	case '2': //Decrease arm angle
		angPata1No -= 3;
		if (angPata1No <= 0) angPata1No = 360;
		glutPostRedisplay();
		break;
	case '3': //Increase forearm angle
		if (angPata3NoX < 90) angPata3NoX += 3;
		glutPostRedisplay();
		break;
	case '4': //Decrease forearm angle
		if (angPata3NoX > -90) angPata3NoX -= 3;
		glutPostRedisplay();
		break;
	case '5': //Increase hand angle
		if (angPata3NoX < 90) angPata3NoX += 3;
		glutPostRedisplay();
		break;
	case '6': //Decrease hand angle
		if (angPata3NoX > -90) angPata3NoX -= 3;
		glutPostRedisplay();
		break;
	case '7': //Increase clamp angle y axis
		if (angGarraDirY < 60) angGarraDirY += 3;
		glutPostRedisplay();
		break;
	case '8': //Decrease clamp angle y axis
		if (angGarraDirY > 0) angGarraDirY -= 3;
		glutPostRedisplay();
		break;
	case '9': //Increase clamp angle z axis
		angGarraDirZ += 3;
		if (angGarraDirZ >= 360) angGarraDirZ = 0;
		glutPostRedisplay();
		break;
	case '0': //Decrease clamp angle z axis
		angGarraDirZ -= 3;
		if (angGarraDirZ <= 0) angGarraDirZ = 360;
		glutPostRedisplay();
		break;
		*/
	case 'C': //Aumenta o ângulo da curvatura do corpo
		//angCurvaCorpo += .9;
		glutPostRedisplay();
		break;
	case 'c': //Diminui o ângulo da curvatura do corpo
		//angCurvaCorpo -= .9;
		glutPostRedisplay();
		break;
	case 'H': //Aumenta o ângulo da curva horizontal da cauda
		//angHorzCauda -= .9;
		glutPostRedisplay();
		break;
	case 'h': //Diminui o ângulo da curva horizontal da cauda
		//angHorzCauda += .9;
		glutPostRedisplay();
		break;
	case 'P': //Aumenta tamanho da pata
		//sizeArm += .2;
		//sizeForearm += .2;
		glutPostRedisplay();
		break;
	case 'p': //Reduz tamanho da pata
		//sizeArm -= .2;
		//sizeForearm -= .9;
		glutPostRedisplay();
		break;
		/*
	case 'M': //Muda lado de visão em relação ao eixo X
		if (angVisaoX == 0) {
			angVisaoX = 90;
		}
		else {
			if (angVisaoX == 90) {
				angVisaoX = 180;
			}
			else {
				if (angVisaoX == 180) {
					angVisaoX = 270;
				}
				else {
					if (angVisaoX == 270) {
						angVisaoX = 0;
					}
					else {
						angVisaoX = 0;
					}
				}
			}
		}
		break;
	case 'm': //Muda lado de visão em relação ao eixo Z
		if (angVisaoZ == 0) {
			angVisaoZ = 90;
		}
		else {
			if (angVisaoZ == 90) {
				angVisaoZ = 180;
			}
			else {
				if (angVisaoZ == 180) {
					angVisaoZ = 270;
				}
				else {
					if (angVisaoZ == 270) {
						angVisaoZ = 0;
					}
					else {
						angVisaoZ = 0;
					}
				}
			}
		}
		break;
		*/
	case 'T': //Liga a textura
		texturaSimNao = true;
		glutPostRedisplay();
		break;
	case 't': //Retira a textura
		texturaSimNao = false;
		glutPostRedisplay();
		break;
	case 'V': //Aumenta o ângulo da curva vertical da cauda
		//angVertCauda -= .9;
		glutPostRedisplay();
		break;
	case 'v': //Diminui o ângulo da curva vertical da cauda
		//angVertCauda += .9;
		glutPostRedisplay();
		break;
	case 'X': //Aumenta o ângulo de visão no eixo X
		//if (angVisaoX > 0) angVisaoX += 3;
		glutPostRedisplay();
		break;
	case 'x': //Reduz o ângulo de visão no eixo X
		//if (angVisaoX < 180) angVisaoX -= 3;
		glutPostRedisplay();
		break;
	case 'Z': //Aumenta o ângulo de visão no eixo Z
		//if (angVisaoZ < 180) angVisaoZ += 3;
		glutPostRedisplay();
		break;
	case 'z': //Reduz o ângulo de visão no eixo Z
		//if (angVisaoZ > 0) angVisaoZ -= 3;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
//Desenha a cena
void desenhaCena(void) {
	// desenha o chão
	desenhaPiso(82.0);
	// desenha o céu
	//desenhaCeu(0.03, 0.03, 81.0);
	glTranslatef(0.0, 0.0, 0.9);
	//desenhaEscorpiao();	
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	//Desenha setas de orientação:
	desenhaSetasOrientacao();
	//desenhaPata();
	glTranslatef(-0.5, 1.0, 2.0);
	desenhaEscorpiao();
	glPopMatrix();
	//desenhaConeCurvado(0.00, 30, 0.00, 360, 7.00, 2.00, 0.3);
	glTranslatef(1, 1, 1);
	//desenhaToro(0.00, 360.00, 0.00, 360.00, 1.0);
	//desenhaElipsoide(0, 180.00, 0.4, 1.2, 0.6);
	//desenhaQuelicera();
	glutSwapBuffers();
}
void inicializaRenderizacao(void) {
	Cameras camera1 = Cameras();
	quadCeu = gluNewQuadric();
	_textIdCeu = loadTexture(nomeArqTextCeu);
	_textIdPiso = loadTexture(nomeArqTextPiso);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}
// Insere a imagem em uma textura e retorna o id da textura
GLuint loadTexture(char *filename) {

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
//Inicializa a iluminação
void inicializaIluminacao(void)
{
	Iluminacao iluminacao = Iluminacao();
}
/* Desenhos */
//Desenha o Céu
void desenhaCeu(float deltaHorz, float deltaVert, float raio) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textIdCeu);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0.0, 0.0, 0.01);
	desenhaSemiEsfera(raio, deltaHorz, deltaVert);
	glPopMatrix();
}
//Desenha escorpiao
void desenhaEscorpiao(void) {
	Escorpiao novoEscorpiao = Escorpiao();
}
//Desenha o piso
void desenhaPiso(float raio)
{
	glBindTexture(GL_TEXTURE_2D, _textIdPiso);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	desenhaDisco(0.00, raio);
}
//Desenha setas de orientação
void desenhaSetasOrientacao(void)
{
	glPushMatrix();
	glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
	glTranslatef(0.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glPopAttrib();
	glPopMatrix();
}

/* Função Main */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Escorpião");
	inicializaIluminacao();
	inicializaRenderizacao();
	glutDisplayFunc(desenhaCena);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(tecladoFuncoesEspeciais);
	glutMouseFunc(gerenciaMouse);
	glutReshapeFunc(handleResize);
	glutIdleFunc(atualizaMovimentosAutomaticos);
	glutMainLoop();
	return 0;
}


