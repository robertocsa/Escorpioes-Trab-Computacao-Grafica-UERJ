/*Testes.Cpp*/
/*Classe utilizada apenas para funcionalidades em teste*/
#include "Testes.h"

Testes::Testes()
{
}

Testes::~Testes()
{
}
void Testes::desenhaPataMovimento(void) {
	glRotatef(angGarraY + 60, 1.0f, 1.0f, 0.0f);
	desenhaCilindro(diametroCilindro / 3, tamPata);
	glTranslatef(0.0f, 0.0f, tamPata + diametroEsfera / 15);
	desenhaEsfera(diametroEsfera / 3);
	glTranslatef(0.0f, 0.0f, diametroEsfera / 15);
	glRotatef(60, 1.0f, 1.0f, 0.0f);
	desenhaCilindro(diametroCilindro / 3, tamPata);
	glTranslatef(0.0f, 0.0f, tamPata + diametroEsfera / 15);
	desenhaEsfera(diametroEsfera / 3);
	glTranslatef(0.0f, 0.0f, diametroEsfera / 15);
	glRotatef(40, 1.0f, 1.0f, 0.0f);
	desenhaCone(diametroCilindro / 3, tamPata);
}
//A função abaixo foi baseada no gráfico Tubo do WinPlot:
void Testes::desenhaConeCurvado(float tMin, float tMax, float uMin, float uMax, float fator1, float fator2, float fator3) {
	glPushMatrix();
	glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
	glColor3f(1.0, 0.0, 0.0);
	tMin = radiano(tMin);
	tMax = radiano(tMax);
	uMin = radiano(uMin);
	uMax = radiano(uMax);
	float deltaU = 0.16;
	float deltaV = 0.1;

	float x = 0.00; float y = 0.00; float z = 0.00; float r = 0.00; float u1 = 0.00;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (float u = tMin; u <= tMax + .01; u += deltaU)
	{
		glBegin(GL_TRIANGLE_STRIP);
		x = cos(fator1 * u);
		y = sin(fator1 * u);
		z = fator2 * u;
		r = fator3 * u;
		//Desenha anéis:
		for (float v = uMin; v < uMax + .001; v += deltaV)
		{
			u1 = u + deltaU;
			glTexCoord2f(u1, v);
			glVertex3f(r*cos(u1), r*cos(u1), z);
			glTexCoord2f(u, v);
			glVertex3f(r*cos(u), r* cos(u), z);
		}
		glEnd();
	}
	glPopAttrib();
	glPopMatrix();
	glutPostRedisplay();
}
