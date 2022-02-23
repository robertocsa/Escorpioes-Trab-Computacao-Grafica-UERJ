/*DesenhaPrimitivas.h 
Classe para os desenhos mais básicos e gerais como o de esferas, cilíndros, elipsóides etc
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

using namespace nsConstantes;

class DesenhaPrimitivas
{
public:
	DesenhaPrimitivas();
	~DesenhaPrimitivas();
	//Variáveis públicas:	

	//Estáticos:
	static GLUquadric *quadSphere;
	static GLUquadric *quadCylinder;
	static GLuint _textureIdSphere;
	static GLuint _textureIdCylinder;	
	static bool texturaSimNao;
	static void desenhaQuelicera(void)
	{
		glPushMatrix();
		glRotatef(-90, 1.00f, 0.00f, 0.00f);
		glRotatef(-90, 0.00f, 1.00f, 0.00f);
		glRotatef(-30, 0.00f, 0.00f, 1.00f);
		glScalef(0.04, 0.06, 0.04);
		float deltaU = 0.015;
		float deltaV = 0.015;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
		float x = 0.00; float y = 0.00; float z = 0.00;
		glBegin(GL_TRIANGLE_STRIP);
		float u1 = 0.00f;
		for (float u = 0.00f; u < 0.3; u += deltaU)
		{
			for (float v = -0.025f; v <= DOIS_PI; v += deltaV)
			{
				u1 = u + deltaU;
				x = (2 + u1 * cos(v))*sin(DOIS_PI * u1);
				y = (2 + u1 * cos(v))*cos(DOIS_PI * u1) + 2 * u1;
				z = u1 * sin(v);
				glTexCoord2f(u1, v);
				glVertex3f(x, y, z);
				x = (2 + u * cos(v))*sin(DOIS_PI * u);
				y = (2 + u * cos(v))*cos(DOIS_PI * u) + 2 * u;
				z = u * sin(v);
				glTexCoord2f(u, v);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
		glPopMatrix();
		glutPostRedisplay();
	}
	static void desenhaElipsoide(float angInicial, float angFinal, float largura, float comprimento, float altura)
	{
		glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		angInicial = ajustaGrau(angInicial);
		angFinal = ajustaGrau(angFinal);
		float deltaU = 0.16;
		float deltaV = 0.1;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
		float x = 0.00; float y = 0.00; float z = 0.00;
		float u1 = 0.00f; float v1 = 0.00f;
		glBegin(GL_TRIANGLE_STRIP);
		for (float u = angInicial; u <= angFinal + .01; u += deltaU)
		{
			//Desenha anéis:		
			for (float v = -0.1; v < DOIS_PI; v += deltaV)
			{
				glTexCoord2f(u, v);
				x = largura * cos(u) * cos(v);
				y = altura * cos(u) * sin(v);
				z = comprimento * sin(u);
				glVertex3f(x, y, z);
				glTexCoord2f(u, v);
				u1 = u + deltaU;
				v1 = v + deltaV;
				glTexCoord2f(u1, v1);
				x = largura * cos(u1) * cos(v1);
				y = altura * cos(u1) * sin(v1);
				z = comprimento * sin(u1);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
		glPopMatrix();
		glutPostRedisplay();
	}
	static void desenhaSemiEsfera(float raio, float deltaHorz, float deltaVert) {
		float u1 = 0.00; float v1 = 0.00;

		float x = 0.0; float y = 0.0; float z = 0.0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CURRENT_TEXTURE_COORDS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CURRENT_TEXTURE_COORDS);
		for (float u = 0.00; u < DOIS_PI; u += deltaHorz) {
			glBegin(GL_QUAD_STRIP);
			for (float v = MEIO_PI; v < PI; v += deltaVert) {
				u1 = u + deltaHorz;
				x = cos(u1) * sin(v);
				y = sin(u1) * sin(v);
				z = cos(v);
				glNormal3f(x, y, z);
				v1 = (v - MEIO_PI);
				glTexCoord2f(u1, v1);
				glVertex3f(raio*x, raio*y, raio*z);
				x = cos(u) * sin(v);
				y = sin(u) * sin(v);
				z = cos(v);
				glNormal3f(x, y, z);
				glTexCoord2f(u, v1);
				glVertex3f(raio*x, raio*y, raio*z);
			}
			glEnd();
		}
	}
	static void desenhaCone(float diametro, float comprimento) {
		if (texturaSimNao) {
			glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			gluQuadricTexture(quadCylinder, 1);
		}
		else
			gluQuadricTexture(quadCylinder, 0);
		gluCylinder(quadCylinder, diametro, 0, comprimento, 40.0, comprimento*30.0);
	}
	static void desenhaCilindro(float diametro, float comprimento) {
		if (texturaSimNao) {
			glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			gluQuadricTexture(quadCylinder, 1);
		}
		else
			gluQuadricTexture(quadCylinder, 0);
		gluCylinder(quadCylinder, diametro, diametro, comprimento, 40.0, comprimento*30.0);
	}
	static void desenhaDisco(float diametroInterno, float diametroExterno) {
		gluQuadricTexture(quadCylinder, 1);
		gluDisk(quadCylinder, diametroInterno, diametroExterno, 32.0, 32.0);
	}
	static void desenhaEsfera(float raio) {
		gluQuadricTexture(quadSphere, 1);
		gluSphere(quadSphere, raio, 32, 32);
	}
	//A função desenhaToro foi baseada no gráfico Tubo do WinPlot:
	// aMax é um percentual do círculo e varia de 0 a 1
	static void desenhaToro(float tMin, float tMax, float uMin, float uMax, float aMax) {
		glPushMatrix();
		glRotatef(90, 0.0, 0.0, 1.0);
		glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
		glColor3f(1.0, 0.0, 0.0);
		tMin = radiano(tMin);
		tMax = radiano(tMax);
		uMin = radiano(uMin);
		uMax = radiano(uMax);
		float divisoesT = 120;
		float divisoesU = 60;
		float deltaT = tMax / divisoesT;
		float deltaU = uMax / divisoesU;
		float x = 0.00; float y = 0.00; float z = 0.00; float r = 0.00; float t1 = 0.00;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);
		for (float t = tMin; t <= tMax + .01; t += deltaT)
		{
			//Desenha anéis:
			for (float u = uMin; u < uMax + .00001; u += deltaU)
			{
				t1 = t + deltaT;
				glTexCoord2f(t1, u);
				glVertex3f((2 + cos(u))*cos(t1*aMax), (2 + cos(u))*sin(t1*aMax), sin(u));
				glTexCoord2f(t, u);
				glVertex3f((2 + cos(u))*cos(t*aMax), (2 + cos(u))*sin(t*aMax), sin(u));
			}
		}
		glEnd();
		glPopAttrib();
		glPopMatrix();
		glutPostRedisplay();
	}
	
	// A função abaixo serve para converter a escala de 0 a 180 graus em radianos equivalentes 
// ao trecho: - pi/2 a pi/2
	static float ajustaGrau(float angulo)
	{
		if (angulo >= 0 && angulo < 90) {
			return -(90 - angulo)*(PI / 180);
		}
		else
		{
			return (angulo - 90)*(PI / 180);
		}
	}	
private:
	GLuint loadTexture(char *filename);	
	GLuint textureId;
};