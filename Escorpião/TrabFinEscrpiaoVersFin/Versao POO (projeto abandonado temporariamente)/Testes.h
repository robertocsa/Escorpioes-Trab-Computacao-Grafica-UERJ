/*Testes.h*/
/*Classe utilizada apenas para funcionalidades em teste*/
#pragma once

#include <iostream>
#include "DesenhaPrimitivas.h"
using namespace std;
using namespace nsConstantes;

class Testes
{
public:
	Testes();
	~Testes();
	void desenhaPataMovimento(void);
	void desenhaConeCurvado(float tMin, float tMax, float uMin, float uMax, float fator1, float fator2, float fator3);
private:
	float angGarraY = 0.00f;
	float diametroEsfera = 4.00f;
	float diametroCilindro = 4.00f;
	float tamPata = 4.00f;
};

