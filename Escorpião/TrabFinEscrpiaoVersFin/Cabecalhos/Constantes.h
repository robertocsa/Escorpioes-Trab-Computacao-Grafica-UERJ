/* Trabalho final da disciplina Computacao Grafica - IME-UERJ
   Aluno: Roberto Carlos dos Santos
   Professor: GILSON ALEXANDRE OSTWALD PEDRO DA COSTA
   2018-2 (entregue em 14/01/2019).

   Arquivo de cabecalho: Constantes.h

   /* Constantes.h
   Serve para guardar os valores de todas as constantes globais */

#pragma once
namespace nsConst
{
	constexpr char* nomeArqTextPiso = ".\\Recursos\\piso.bmp";
	constexpr char* nomeArqTextPele = ".\\Recursos\\pele.bmp";
	constexpr char* nomeArqTextQuelicera = ".\\Recursos\\quelicera.bmp";
	constexpr char* nomeArqTextPata = ".\\Recursos\\pata.bmp";
	constexpr char* nomeArqTextCeu = ".\\Recursos\\ceu.bmp";

	constexpr auto NUM_ESCORPIOES = 2;  
	constexpr auto NUM_LUZES = 4; //Para futura implementação
	constexpr auto NUM_CAMERAS = 4; 
	constexpr auto PI = 3.14159265f;
	constexpr auto DOIS_PI = 6.28318530f;
	constexpr auto MEIO_PI = 1.57079632f;
	constexpr auto RADIANO = (PI / 180.00f);	
	constexpr auto ESC = 27;
	constexpr auto TAB = 9;
	constexpr auto ENTER = 13;
	constexpr auto TECLA_5 = 112;

	//Constantes das texturas:
	constexpr auto SEM_TEXTURA = 0;
	constexpr auto TEXTURA_PELE = 1 << 0;
	constexpr auto TEXTURA_QUELICERA = 1 << 1;
	constexpr auto TEXTURA_PATA = 1 << 2;
	constexpr auto TEXTURA_CEU = 1 << 3;
	constexpr auto TEXTURA_PISO = 1 << 4;

	/*Estruturas globais*/
	typedef struct _Foco {
		float x;
		float y;
		float z;
	};
	typedef struct _Pos {
		float x;
		float y;
		float z;
	};
	typedef struct _Inclin {
		float x;
		float y;
		float z;
	};
	typedef struct _AngVisao {
		float x = 15.0;
		float y = 15.0;  //Somente usado para fins de projeção (não é usado na matriz de modelagem)
		float z = 15.0;
	};
	typedef struct _AtribCeu {
		float x = 70.0;
		float z = 0.0;
		float raio = 3.0;
	};
	typedef struct _AtribCmra {
		int id;
		bool ativa;
		float distOlhar;
		_Foco foco;
		_Pos pos;
		_AngVisao angVisao;
		_Inclin angInclin;
	};
	typedef struct _DimPata {
		float larg = 0.025f;
		float compr = 0.08f;
		float alt = 0.018f;
	};
	typedef struct _DimTelaPadrao {
		float x=800.00f;
		float y=800.00f;
	};

	static float radiano(GLfloat grau) {
		return grau * RADIANO;
	}	
	static void giraX(GLfloat angulo) {
		glRotatef(angulo,1.0f, 0.0f,0.0f);
	}
	static void giraY(GLfloat angulo) {
		glRotatef(angulo, 1.0f, 0.0f, 0.0f);
	}
	static void giraZ(GLfloat angulo) {
		glRotatef(angulo, 1.0f, 0.0f, 0.0f);
	}
	void texto(char* strTexto, int x, int y, int z, void* fonte)
	{		
		glRasterPos3f(x, y, z);
		int tam = strlen(strTexto);
		for (int i = 0; i < tam; i++) {
			glutBitmapCharacter(fonte, strTexto[i]);
		}
	}
	void texto(char* strTexto)
	{
		glRasterPos3f(0.0, 0.0, 0.0);
		int tam = strlen(strTexto);
		for (int i = 0; i < tam; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, strTexto[i]);
		}
	}
	void vermelho(void) {
		glColor3f(1.0, 0.0, 0.0);
	}
	void verde(void) {
		glColor3f(0.0, 1.0, 0.0);
	}
	void azul(void) {
		glColor3f(0.0, 0.0, 1.0);
	}
	void popPush(void) {
		glPopMatrix();
		glPushMatrix();
	}
}

