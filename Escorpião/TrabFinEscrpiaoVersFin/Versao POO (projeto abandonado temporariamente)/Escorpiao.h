/* Escorpiao.h
Classe Escorpião 
Desenha os escorpiões
*/
#pragma once
#include <GL/glut.h>
#include "DesenhaPrimitivas.h"
#include "Constantes.h"

using namespace std;
using namespace nsConstantes;

class Escorpiao {
public:
	float diametroCilindro = 0.3;
	float diametroEsfera = 0.4;
	float angCurvaCorpo = 0.0;
	float angVertCauda = 0.0;
	float angHorzCauda = 0.0;
	float angGarraDirY = 0.0;
	float angGarraDirZ = 0.0;
	float angGarraEsqY = 0.0;
	float angGarraEsqZ = 0.0;
	float angPata1NoY = 0.0;
	float angPata1NoZ= 0.0;
	float angPata2NoX = 0.0;
	float angPata2NoZ = 0.0;
	float angPata3NoX = 90.0;
	float angPata3NoZ = 0.0;
	float tamPata = 1.0;
	float sizeArm = 4.5;
	float sizeForearm = 3.0;
	float abertQuelicera = 0.09;
	float escalaYQuel = 0.017;		
	
	GLuint _textIdPele;	
	GLuint _textIdQuelicera;	
	GLuint _textIdPata;
	bool abrindoQuelicera = true;
	bool curvandoCorpo = true;
	GLuint loadTexture(char *filename);
	Escorpiao();
	Escorpiao(int idEscorpiao);
	int obtemIdEscorpiao(void);
	void inicializaRenderizacao(void);
	void inicializaIluminacao(void);
	void desenhaPata(void);
	void desenhaEscorpiao();
	void atualizaMovimentosAutomaticos(void);
	void desenhaEscorpiao(_pos _posicao);
	void desenhaOlhos(void);
	void desenhaCauda(void);
	void alteraPosicao(_pos _posicao);
	_pos obtemPosicao(_pos _posicao);
private:
	int idEscorpiao;
	_pos posicao;
};

/*//////////////////////////////////////////////////////////////////////////////////*/

/*Classe Escorpiões
Controla os objetos escorpiao */

class Escorpioes {
public:
	//Construtor:
	Escorpioes() {
		this->criaNovoEscorpiao();
	}	
	//Statics:
	static int obtemNovoId(void)
	{
		int i = 0;
		for (i = 1; i < 7; i++) {
			if (listaEscorpioes == NULL) {
				return i;
			}
		}
		return 0;
	}
	static int obtemIdEscorpiaoAtivo(void)
	{
		return idEscorpiaoAtivo;
	}
	static Escorpiao obtemObjEscorpiaoAtivo(void) {
		return listaEscorpioes[idEscorpiaoAtivo];
	}
	static void atualizaMovimentosAutomaticos(void) {
		//Atualizacao automatica de parâmetros dos escorpiões
	}
	static void atualizaPosicaoEscorpioes() {
	}
	static Escorpiao criaNovoEscorpiao(void)
	{
		int idNovoEscorpiao = obtemNovoId();
		if (idNovoEscorpiao != 0) {
			listaEscorpioes[idNovoEscorpiao] = Escorpiao(idNovoEscorpiao);
			return listaEscorpioes[idNovoEscorpiao];
		}
		return NULL;
	}
	static void alteraEscorpiaoAtivo(int escorpiaoAtivo)
	{
		idEscorpiaoAtivo = escorpiaoAtivo;
	}
	static void encerraEscorpiao(int escorpiao)
	{
		int outroEscorpiao = existeOutroEscorpiao(escorpiao);
		if (outroEscorpiao != 0) {
			encerraEscorpiao(escorpiao);
		}
		else {
			encerraEscorpiao(escorpiao);
			cout << "Não há mais escorpiões após o fim do escorpião de id: " << escorpiao << "." << endl;
		}
	}
	static int existeOutroEscorpiao(int idEscorpiao) {
		int i = 0;
		for (i = 0; i < 7; i++) {
			if (listaEscorpioes[i].obtemIdEscorpiao() != 0 &&
				listaEscorpioes[i].obtemIdEscorpiao() != idEscorpiao) {
				return i;
			}
		}
		return 0;
	}

private:
	static int idEscorpiaoAtivo;
	static Escorpiao listaEscorpioes[NUM_ESCORPIOES];
};
