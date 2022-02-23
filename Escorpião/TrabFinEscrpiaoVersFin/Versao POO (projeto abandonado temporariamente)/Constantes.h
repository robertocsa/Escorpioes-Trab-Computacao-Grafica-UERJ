/* Constantes.h 
   Serve para guardar os valores de todas as constantes globais */
#pragma once
//#ifndef CONSTANTES_H
//#define CONSTANTES_H

namespace nsConstantes
{

#define desenhaEsfera DesenhaPrimitivas::desenhaEsfera
#define desenhaSemiEsfera DesenhaPrimitivas::desenhaSemiEsfera
#define desenhaCilindro DesenhaPrimitivas::desenhaCilindro
#define desenhaDisco DesenhaPrimitivas::desenhaDisco
#define desenhaCone DesenhaPrimitivas::desenhaCone
#define desenhaElipsoide DesenhaPrimitivas::desenhaElipsoide
#define desenhaQuelicera DesenhaPrimitivas::desenhaQuelicera
	
	constexpr auto NUM_ESCORPIOES = 7;
	constexpr auto NUM_LUZES = 4;
	constexpr auto NUM_CAMERAS = 7;
	constexpr auto PI = 3.14159265358979;
	constexpr auto DOIS_PI = 6.28318530717959;
	constexpr auto MEIO_PI = 1.5707963267949 ;
	constexpr auto RADIANO = (PI / 180);	

	char* nomeArqTextPiso = "./piso.bmp";
	char* nomeArqTextCeu = "./ceu.bmp";
	char* nomeArqTextPele = "./pele.bmp";
	char* nomeArqTextQuelicera = "./quelicera.bmp";
	char* nomeArqTextPata = "./pata.bmp";

	/*Estruturas globais*/
	struct _foco {
		float x;
		float y;
		float z;
	};
	struct _pos {
		float x;
		float y;
		float z;
	};
	struct _angVisao {
		float x = 15.0;
		float z = 15.0;
	};
	struct _camera {
		int id;
		bool ativa;
		float distOlhar;
		_foco foco;
		_pos pos;
		_angVisao angVisao;
	};
/*
	static float aleatorio(float min, float max){
		static float numAleat;
		float temp = numAleat + 0.124 / 1358;
		numAleat = temp;
		return (max - min)*(numAleat) + min;
	}*/

	static float radiano(float grau) {
		return grau * RADIANO;
	}	
}
//#endif
