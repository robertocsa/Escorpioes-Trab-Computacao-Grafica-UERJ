/* Trabalho final da disciplina Computacao Grafica - IME-UERJ
   Aluno: Roberto Carlos dos Santos
   Professor: GILSON ALEXANDRE OSTWALD PEDRO DA COSTA
   2018-2 (entregue em 14/01/2019). 
   
   Arquivo de cabecalho: Principal.h

*/

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include "..\Cabecalhos\RgbImage.h"
#include "..\Cabecalhos\Constantes.h"

using namespace nsConst;
using namespace std;
//using namespace nsPrim;

GLfloat diametroCilindro = 0.04;
GLfloat raioEsfera = 0.4;
GLfloat angCurvaCorpo = 0.0;
GLfloat angVertCauda = 0.0;
GLfloat angHorzCauda = 0.0;
GLfloat angApoioPataY = 0.0;
GLfloat angApoioPataZ = 0.0;
GLfloat angRotGarra = 0.0;
GLfloat angApoioGarra = -55.0;
GLfloat angMeioGarra = 0.0;
GLfloat angAbertGarra = 0.0;
GLfloat tamPata = 1.0;
GLfloat tamGarra = 0.1429f;
GLfloat altEscorpiao = 1.2;
GLfloat abertQuelicera = 0.029;
GLfloat escalaYQuel = 0.017;
GLfloat rx, ry; // Para testes
GLfloat raioCurvaCorpo = 100.0;
int contaPassgs = 0;

/* Variáveis para teste do programa */
float vTeste1 = 0.00f;
float vTeste2 = 0.00f;
float vTeste3 = 0.00f;
typedef struct _dbPos {
	float x;
	float y;
	float z;
};
_dbPos dbPos;
bool ligaEsferaDebug = true;
void informaPosicao(void);
/*/////////////////////////////////////*/

int idCameraAtiva = 1;
_AtribCmra atribCamera;
_AtribCeu atribCeu;
_AngVisao angProjecao;
_DimTelaPadrao dimTelaPadrao;
_DimPata dimPata;
_Pos posMouse;

GLfloat luz_ambiente[4] = { 0.8, 0.8, 0.8, 1.0 };

GLfloat posicaoLuz0[4] = { 0.0f, 0.0f, 25.0f, 1.0 };
GLfloat luzAmbiente0[4] = { 0.39, 0.39, 0.39, 1.0 };
GLfloat luzDifusa0[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat especularidade0[4] = { 0.3, 0.3, 0.3, 1.0 };

GLfloat posicaoLuz1[4] = { 0.0f, 1.0f, 10.0f, 1.0 };
GLfloat luzAmbiente1[4] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat luzDifusa1[4] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat especularidade1[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat especulrdadeTexturaDeslg[4] = { 1.0, 1.0, 1.0, 1.0 };

GLUquadric *quadSphere;
GLUquadric *quadCylinder;
GLUquadric *quadCeu;

GLuint _textureIdSphere;
GLuint _textureIdCylinder;

GLfloat especMaterialTexture0 = 30;
GLfloat especMaterialTexture1 = 70;
GLfloat especMaterialTexturaDeslg = 60;

GLuint _textIdPiso;
GLuint _textIdPele;
GLuint _textIdQuelicera;
GLuint _textIdPata;
GLuint _textIdCeu;

bool texturaLigada = true;
bool abrindoQuelicera = true;
bool abrindoGarra = true;
bool curvandoCauda = true;
bool curvandoCorpo = true;
bool desenhaCeuLig = true;
bool desenhaPisoLig = true;
bool ligaSetasOrient = true;
bool desenhaEscorpiaoLig = true;
bool fundoBrancoSim = true;
bool ligaWireFrame = false;
bool semMovimentosAutomaticos = false;

void atualizaMovimentosAutomaticos(void);
void inicializaRenderizacao(void);
void parametrosCameras(void);
void teclado(unsigned char tecla, int x, int y);
GLuint loadTexture(char *filename);
void desenhaElipsoide(float angInicial, float angFinal, float largura, float comprimento,  float altura);
void desenhaElipsoide(float largura, float comprimento,  float altura);
void desenhaElipsoide(float escala);
float ajustaGrau(float angulo);
//desenhos do escorpião
void desenhaEscorpiao(void);
void desenhaCabeca(void);
void desenhaPataDir(void);
void desenhaPataEsq(void);
void desenhaGarraDir(void);
void desenhaGarraEsq(void);
void desenhaPontaGarra(float sx, float sy, float sz);
void desenha2Patas(int idPar);
//void desenha4Patas(void);
void desenha8Patas(void);
void desenhaOlhos(void);
void desenhaCauda(void);
//Desenhos de primitivas
void desenhaEsfera(float raio);
void desenhaEsfera(void);
void desenhaSemiEsfera(float raio, float largTextura, float altTextura);
void desenhaQuelicera(void);
void desenhaQuelicera(float sx, float sy, float sz);
void desenhaCilindro(float raioBase, float raioTopo, float comprimento);
void desenhaCilindro(float raio, float comprimento);
//Desenho de cenários
void alteraTexturas(int textura);
void desenhaCeu(void);
void desenhaPiso(void);
void desenhaSetasOrientacao(void);
void desenhaCena(void);
void atualizaPosicaoOlhos(void);
void centralizaCena(void);
void trocaCameraAtiva(void);
void redimVisao(int w, int h);
void parametrosIluminacao(void);
void movimento(int x, int y);
void escreveSobreTrabalho(void);

GLuint textureId;