/* Trabalho final da disciplina Computacao Grafica - IME-UERJ
   Aluno: Roberto Carlos dos Santos
   Professor: GILSON ALEXANDRE OSTWALD PEDRO DA COSTA
   2018-2 (entregue em 14/01/2019). 

 // Arquivo Principal.cpp : Este arquivo contém a função 'main'. //
*/

#include "..\Cabecalhos\Principal.h"

/*Inicialização*/
void inicializaRenderizacao(void) { 
	idCameraAtiva = 1;
	centralizaCena();
	quadSphere = gluNewQuadric();
	quadCylinder = gluNewQuadric();
	quadCeu = gluNewQuadric();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	_textIdQuelicera = loadTexture(nomeArqTextQuelicera);
	_textIdPiso = loadTexture(nomeArqTextPiso);
	_textIdPele = loadTexture(nomeArqTextPele);
	_textIdPata = loadTexture(nomeArqTextPata);
	_textIdCeu = loadTexture(nomeArqTextCeu);

	atualizaPosicaoOlhos();
}
void parametrosCameras(void)
{
	int idCam = idCameraAtiva;
	switch (idCam) {
		case 1:   //Visão perspectiva
			atribCamera.angVisao.x = 180.0f;
			atribCamera.angVisao.z = 10.0f;
			atribCamera.distOlhar = 8.0f;
			//Posição dos olhos: esférica em torno da cena:
			atualizaPosicaoOlhos();
			atribCamera.foco.x = 0.00f;
			atribCamera.foco.y = 0.00f;
			atribCamera.foco.z = 0.00f;
			atribCamera.angInclin.x = 0.00f;
			atribCamera.angInclin.y = 0.00f;
			atribCamera.angInclin.z = 1.00f;
			cout << "Câmera ativa: 1" << endl;
			break;
		case 2:   //Visão perspectiva com outro angulo de visao
			atribCamera.angVisao.x = 30;
			atribCamera.angVisao.z = 30;
			atribCamera.distOlhar = 9;
			atribCamera.foco.x = 0.00f;
			atribCamera.foco.y = 0.00f;
			atribCamera.foco.z = 0.00f;
			atribCamera.pos.x = 0.00f;
			atribCamera.pos.y = 0.00f;
			atribCamera.pos.z = 3.00f;
			atribCamera.angInclin.x = 0.00f;
			atribCamera.angInclin.y = 0.00f;
			atribCamera.angInclin.z = 1.00f;
			cout << "Câmera ativa: 2" << endl;
			break;
		case 3:    // Visão ortogonal
			atribCamera.angVisao.x = 30.0f;
			atribCamera.angVisao.z = 30.0f;
			atribCamera.distOlhar = 12.0f;
			atribCamera.foco.x = 1.0f;
			atribCamera.foco.y = 0.00f;
			atribCamera.foco.z = altEscorpiao*2;
			atribCamera.pos.x = -1.00f;
			atribCamera.pos.y = 0.00f;
			atribCamera.pos.z = altEscorpiao*2;
			atribCamera.angInclin.x = 0.00f;
			atribCamera.angInclin.y = 0.00f;
			atribCamera.angInclin.z = 1.00f;
			cout << "Câmera ativa: 3" << endl;
			break;
		case 4:   //Visão Frustum
			atribCamera.angVisao.x = 30;
			atribCamera.angVisao.z = 30;
			atribCamera.distOlhar = 9.4f;
			atribCamera.foco.x = 1.00f;
			atribCamera.foco.y = 0.00f;
			atribCamera.foco.z = altEscorpiao;
			atribCamera.pos.x = 1.00f;
			atribCamera.pos.y = 0.00f;
			atribCamera.pos.z = altEscorpiao * 2;
			atribCamera.angInclin.x = 0.00f;
			atribCamera.angInclin.y = 0.00f;
			atribCamera.angInclin.z = 1.00f;
			cout << "Câmera ativa: 4" << endl;
			break;
		default:
			break;
	}
}

//A função abaixo veio do arquivo de exemplo (Garras). Não foi modificada.
//makes the image into a texture, and returns the id of the texture
GLuint loadTexture(char *filename) {
	
	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	if (texturaLigada) glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
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
//Inicializa a iluminação (LIGHT0)
void inicializaIluminacao(void)
{
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);	

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente1);

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
}
/*Controles*/
//Função callback chamada para gerenciar os eventos de teclado
void teclado(unsigned char tecla, int x, int y) {
	int teclasFuncao = glutGetModifiers();
	switch (tecla) {
	case ESC: //tecla escape
		exit(0);		
	case TAB: //Tecla TAB (realiza a troca de tipos de visao/cameras
		cout << "TAB" << endl;
		trocaCameraAtiva();
		redimVisao(dimTelaPadrao.x, dimTelaPadrao.y);
		break;
	case 'A': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.x += .05;
		cout << dbPos.x << endl;
		break;
	case 'a': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.x -= .05;
		cout << dbPos.x << endl;
		break;
	case 'D': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.y += .05;
		cout << dbPos.y << endl;
		break;
	case 'd': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.y -= .05;
		cout << dbPos.y << endl;
		break;
	case 'B': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.z += .05;
		cout << dbPos.z << endl;
		break;
	case 'b': //Debug (foi utilizada para movimentação da bolinha de posicionamento dos elementos da imagem)
		dbPos.z -= .05;
		cout << dbPos.z << endl;
		break;		
	case 'C': //Aumenta o ângulo da curvatura do corpo
		if (angCurvaCorpo < 10.2) angCurvaCorpo += .2;
		cout << angCurvaCorpo << endl;
		break;
	case 'c': //Diminui o ângulo da curvatura do corpo
		if (angCurvaCorpo > -5.2) angCurvaCorpo -= .2;
		cout << angCurvaCorpo << endl;
		break;		
	case 'E': //Aumenta o tamanho da pata
		if(dimPata.larg < 0.15f) dimPata.larg += 0.001f;
		cout << "Largura X da pata: " << dimPata.larg << endl;
		break;
	case 'e': //Reduz o tamanho da pata
		if (dimPata.larg > 0.025f)dimPata.larg -= 0.001f;
		cout << "Largura X da pata: " << dimPata.larg << endl;
		break;
	case 'g': //Reduz tamanho da garra
		if (tamGarra > 0.1f) tamGarra -= .01;
		cout << tamGarra << endl;
		break;
	case 'G': //Aumenta tamanho da garra
		if (tamGarra < 0.2f) tamGarra += .01;
		cout << tamGarra << endl;
		break;
	case 'H': //Aumenta o ângulo da curva horizontal da cauda
		if (angHorzCauda > -25.0) angHorzCauda -= .9;
		cout << angHorzCauda << endl;
		break;
	case 'h': //Diminui o ângulo da curva horizontal da cauda
		if (angHorzCauda < 25.0) angHorzCauda += .9;
		cout << angHorzCauda << endl;
		break;
	case 'i': //Liga e desliga o desenho do escorpião
		desenhaEscorpiaoLig ? desenhaEscorpiaoLig = false : desenhaEscorpiaoLig = true;
		cout << "Desenho do escorpião ligado? "<< desenhaEscorpiaoLig << endl;
		break;
	case 'l': //Muda lado de visão no eixo Z
		if (atribCamera.angVisao.z == 0) {
			atribCamera.angVisao.z = 90;
		}
		else {
			if (atribCamera.angVisao.z == 90) {
				atribCamera.angVisao.z = 180;
			}
			else {
				if (atribCamera.angVisao.z == 180) {
					atribCamera.angVisao.z = 270;
				}
				else {
					if (atribCamera.angVisao.z == 270) {
						atribCamera.angVisao.z = 0;
					}
					else {
						atribCamera.angVisao.z = 0;
					}
				}
			}
		}
		break;
	case 'm': //Muda lado de visão no eixo X
		if (atribCamera.angVisao.x == 0) {
			atribCamera.angVisao.x = 90;
		}
		else {
			if (atribCamera.angVisao.x == 90) {
				atribCamera.angVisao.x = 180;
			}
			else {
				if (atribCamera.angVisao.x == 180) {
					atribCamera.angVisao.x = 270;
				}
				else {
					if (atribCamera.angVisao.x == 270) {
						atribCamera.angVisao.x = 0;
					}
					else {
						atribCamera.angVisao.x = 0;
					}
				}
			}
		}
		break;
	case 'n': //Desliga a textura
		texturaLigada ? texturaLigada = false: texturaLigada =true;
		break;
	case 'o': //Liga e desliga o desenho do ceu
		desenhaCeuLig ? desenhaCeuLig = false : desenhaCeuLig = true;
		cout << desenhaCeuLig << endl;
		break;
	case 'p': //Liga e desliga o desenho do piso
		desenhaPisoLig? desenhaPisoLig = false: desenhaPisoLig=true;
		cout << desenhaPisoLig << endl;
		break;	
	case 'Q': //Aumenta o tamanho da pata
		if (dimPata.compr < 0.40f) {
			dimPata.compr += 0.001f;
			altEscorpiao += 0.001f;
		}
		cout << "Comprimento da pata: "<< dimPata.compr << endl;
		break;
	case 'q': //Reduz o tamanho da pata
		if (dimPata.compr > 0.30f) {
			dimPata.compr -= 0.001f;
			altEscorpiao -= 0.001f;
		}
		cout << "Comprimento da pata: " << dimPata.compr << endl;
		break;
	case 'r': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste1 += 0.16f;
		cout << "Valor do parâmetro em teste (vTeste1): " << vTeste1 << endl;
		break;
	case 'R': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste1 -= 0.16f;
		cout << "Valor do parâmetro em teste (vTeste1): " << vTeste1 << endl;
		break;
	case 's': //Liga ou desliga setas de orientação
		ligaSetasOrient? ligaSetasOrient=false: ligaSetasOrient=true;
		cout << "Setas ligadas? = " << ligaSetasOrient << endl;
		break;
	case 't': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste2 += 0.16f;
		cout << "Valor do parâmetro em teste: (vTeste2) " << vTeste2 << endl;
		break;
	case 'T': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste2 -= 0.16f;
		cout << "Valor do parâmetro em teste: (vTeste2) " << vTeste2 << endl;
		break;
	case 'u': //Liga ou desliga fundo branco
		fundoBrancoSim ? fundoBrancoSim = false : fundoBrancoSim = true;
		cout << "Fundo branco? = " << fundoBrancoSim << endl;
		break;
	case 'V': //Aumenta o ângulo da curva vertical da cauda
		if (angVertCauda > -80.0) angVertCauda -= .9;
		cout << angVertCauda << endl;
		break;
	case 'v': //Diminui o ângulo da curva vertical da cauda
		if (angVertCauda < -10.0) angVertCauda += .9;
		cout << angVertCauda << endl;
		break;
	case 'W': //Aumenta o tamanho da pata
		if (dimPata.alt < 0.07f) dimPata.alt += 0.001f;
		cout << "Altura Z da pata: " << dimPata.alt << endl;
		break;
	case 'w': //Reduz o tamanho da pata
		if (dimPata.alt > 0.03f) dimPata.alt -= 0.001f;
		cout << "Altura Z da pata: " << dimPata.alt << endl;
		break;
	case 'x': //Angulo x do Ceu
		atribCeu.x -= 10.0;
		cout << "Angulo x do Ceu: " << atribCeu.x << endl;
		break;
	case 'X': //Angulo x do Ceu
		atribCeu.x += 10.0;
		cout << "Angulo x do Ceu: " << atribCeu.x << endl;
		break;
	case 'y': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste3 += 0.16f;
		cout << "Valor do parâmetro em teste (vTeste3): " << vTeste3 << endl;
		break;
	case 'Y': //Variável de testes (para posicionamentos dos elementos de desenho)
		vTeste3 -= 0.16f;
		cout << "Valor do parâmetro em teste (vTeste3): " << vTeste3 << endl;
		break;
	case 'z': //Angulo z do Ceu
		atribCeu.z -= 10.0;
		cout << "Angulo z do Ceu: " << atribCeu.z << endl;
		break;
	case 'Z': //Angulo z do Ceu
		atribCeu.z += 10.0;
		cout << "Angulo z do Ceu: " << atribCeu.z << endl;
		break;
	case ENTER: //Reduz o ângulo de abertura da garra
		if (angAbertGarra > 10) angAbertGarra -= 3;
		cout << "Angulo de abertura da garra: " << angAbertGarra << endl;
		break;
	case '0': //Aumenta o ângulo de abertura da garra
		if (angAbertGarra < 35) angAbertGarra += 3;
		cout << "Angulo de abertura da garra: " << angAbertGarra << endl;
		break;
	case '1': //Reduz o ângulo de apoio da garra
		if (angApoioGarra > -180) angApoioGarra -= 3;
		cout << "Angulo de apoio da garra: " << angApoioGarra << endl;
		break;	
	case '2': //Reduz o ângulo de apoio da Pata em Y
		if (angApoioPataY > -15.00f) {
			angApoioPataY -= 1;
			altEscorpiao -= 0.0095f;
		}
		cout << "Angulo de apoio da pata em Y: " << angApoioPataY << endl;
		break;
	case '3': //Angulo de rotação da garra
		angRotGarra -= 3;
		if (angRotGarra <= 0) angRotGarra = 360;
		cout << "Angulo de rotação da garra: " << angRotGarra << endl;
		break;	
	case '4': //Reduz o ângulo de apoio da Pata em Z
		if (angApoioPataZ >= -60) angApoioPataZ -= 3;
		cout << "Angulo de apoio da pata em Z: " << angApoioPataZ << endl;
		break;
	case '5': //Aumenta o ângulo do meio da garra		
		if (angMeioGarra < 50.0f) angMeioGarra += 1.5;
		cout << angMeioGarra << endl;
		break;		
	case '6': //Aumenta o ângulo de apoio da Pata em Z
		if (angApoioPataZ <= 70) angApoioPataZ += 3;
		cout << "Angulo de apoio da pata em Z: " << angApoioPataZ << endl;
		break;
	case '7': //Aumenta o ângulo de apoio da garra
		if (angApoioGarra < 180) angApoioGarra += 3;
		cout << "Angulo de apoio da garra: " << angApoioGarra << endl;
		break;
	case '8': //Aumenta o ângulo de apoio da Pata em Y
		if (angApoioPataY < 20.00f) {
			angApoioPataY += 1;
			altEscorpiao += 0.0095f;
		}
		cout << "Angulo de apoio da pata em Y: " << angApoioPataY << endl;
		break;
	case '9': //Angulo de rotação da garra
		angRotGarra += 3;
		if (angRotGarra >= 360) angRotGarra = 0;
		cout << "Angulo de rotação da garra: " << angRotGarra << endl;
		break;
	case '>':
		//Reduz o valor de x da inclinação do olhar
		glMatrixMode(GL_PROJECTION);
		angProjecao.x -= 0.5;
		if (angProjecao.x > -4.0) glRotatef(-0.5, 1.0, 0.0, 0.0);
		//atribCamera.foco.x -= .9;
		break;
	case '<':		
		//Aumenta o valor de x da inclinação do olhar
		glMatrixMode(GL_PROJECTION);
		angProjecao.x += 0.5;
		if (angProjecao.x < 50.0) glRotatef(0.5, 1.0, 0.0, 0.0);
		//atribCamera.foco.x += .9;
		break;
	case ',':
		//Reduz o valor de y da inclinação do olhar
		glMatrixMode(GL_PROJECTION);
		angProjecao.y -= .5;
		if (angProjecao.y > -90.0) glRotatef(-0.5, 0.0, 1.0, 0.0);
		break;
	case '.':
		//Aumenta o valor de y da inclinação do olhar
		glMatrixMode(GL_PROJECTION);
		angProjecao.y += .5;
		if (angProjecao.y < 90.0) glRotatef(0.5, 0.0, 1.0, 0.0);
		break;
	case '+': 
		if (teclasFuncao == GLUT_ACTIVE_CTRL) {
			//Aumenta angulo de visao do eixo Z
			if (atribCamera.angVisao.z < 120) atribCamera.angVisao.z += 3;
		}
		else {
			//Aumenta angulo de visao do eixo X
			if (atribCamera.angVisao.x < 120) atribCamera.angVisao.x += 3;
		}
		break;
	case '-': 
		if (teclasFuncao == GLUT_ACTIVE_CTRL) {
			//Reduz angulo de visao do eixo Z
			if (atribCamera.angVisao.z > 0) atribCamera.angVisao.z -= 3;
		}
		else {
			//Aumenta angulo de visao do eixo X
			if (atribCamera.angVisao.x > 0) atribCamera.angVisao.x -= 3;
		}
		break;
	case '/':
		ligaEsferaDebug ? ligaEsferaDebug = false : ligaEsferaDebug = true;
		cout << "Debug ligado? " << ligaEsferaDebug << endl;
		break;
	case ']':
		ligaWireFrame ? ligaWireFrame = false : ligaWireFrame = true;
		cout << "Wireframe ligado? " << ligaWireFrame << endl;
		break;
	case '\\':
		semMovimentosAutomaticos ? semMovimentosAutomaticos = false : semMovimentosAutomaticos = true;
		cout << "Modo automático ligado? " << semMovimentosAutomaticos << endl;
		break;
	default:
		break;
	}
	atualizaPosicaoOlhos();
	glutPostRedisplay();
}
//Função callback chamada para gerenciar os eventos de teclas de função especial do teclado
void tecladoFuncoesEspeciais(int tecla, int x, int y) {	
	int teclasFuncao = glutGetModifiers();
	cout << "Teclas função: "<< teclasFuncao <<", Tecla: "<< tecla << endl;
	if (teclasFuncao == 0.00) {
		cout << "Tecla de função 0" << endl;
		switch (tecla) {		
		case GLUT_KEY_UP:
			if (atribCamera.angVisao.z > 1.0) atribCamera.angVisao.z -= 1.0;
			cout << "Angulo de visao Z: " << atribCamera.angVisao.z << endl;
			break;
		case GLUT_KEY_DOWN:
			if (atribCamera.angVisao.z < 179.0) atribCamera.angVisao.z += 1.0;
			cout << "Angulo de visao Z: " << atribCamera.angVisao.z << endl;
			break;
		case GLUT_KEY_RIGHT:
			atribCamera.angVisao.x -= 1.0;
			cout << "Angulo de visao X: " << atribCamera.angVisao.x << endl;
			break;
		case GLUT_KEY_LEFT:
			atribCamera.angVisao.x += 1.0;
			cout << "Angulo de visao X: " << atribCamera.angVisao.x << endl;
			break;
		case GLUT_KEY_PAGE_UP:
			atribCamera.distOlhar += 0.1;
			cout << "distância do olhar: " << atribCamera.distOlhar << endl;
			break;
		case GLUT_KEY_PAGE_DOWN:
			atribCamera.distOlhar -= 0.1;
			cout << "distância do olhar: "<< atribCamera.distOlhar << endl;	
			break;
		case GLUT_KEY_HOME:		
			//Centraliza Cena
			centralizaCena();			
			break;
		case GLUT_KEY_END:
			atribCamera.angInclin.x += 1.5;
			break;
		case (GLUT_KEY_END | GLUT_ACTIVE_ALT):
			atribCamera.angInclin.x -= 1.5;
			break;
		default:
			break;
		}
		//if (tecla != GLUT_KEY_HOME) {
		atualizaPosicaoOlhos();
		//}		
	}
	else {
		if (teclasFuncao == GLUT_ACTIVE_CTRL) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				atribCamera.foco.x += 1.5;
				break;
			case GLUT_KEY_LEFT:
				atribCamera.foco.y += 1.5;
				break;
			case GLUT_KEY_PAGE_DOWN:
				atribCamera.distOlhar -= 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == GLUT_ACTIVE_ALT) {
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				atribCamera.pos.x += 1.5;
				break;
			case GLUT_KEY_LEFT:
				atribCamera.pos.y += 1.5;
				break;
			case GLUT_KEY_UP:
				atribCamera.pos.z += 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == (GLUT_ACTIVE_CTRL & GLUT_ACTIVE_SHIFT) ) {
			cout << "Ctrl+Shift"<<endl;
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				atribCamera.foco.x -= 1.5;
				break;
			case GLUT_KEY_LEFT:
				atribCamera.foco.y -= 1.5;
				break;
			case GLUT_KEY_UP:
				atribCamera.foco.z -= 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == (GLUT_ACTIVE_CTRL & GLUT_ACTIVE_ALT)) {
			cout << "Ctrl+Alt"<<endl;
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				atribCamera.pos.x -= 1.5;
				break;
			case GLUT_KEY_LEFT:
				atribCamera.pos.y -= 1.5;
				break;
			case GLUT_KEY_UP:
				atribCamera.pos.z -= 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == (GLUT_KEY_INSERT)) {
			cout << "Aumenta valores" << endl;
			switch (tecla) {
			case GLUT_KEY_RIGHT:
				dbPos.x += 1.5;
				break;
			case GLUT_KEY_LEFT:
				dbPos.y += 1.5;
				break;
			case GLUT_KEY_UP:
				dbPos.z += 1.5;
				break;
			default:
				break;
			}
		}
		if (teclasFuncao == GLUT_ACTIVE_SHIFT){
			cout << "Active Shift" << endl;
			if (tecla == TECLA_5) {    
				cout << "tecla 5" << endl;
				if (angMeioGarra > -180.0f) angMeioGarra -= 1.5;
				cout << angMeioGarra << endl;
			}
		}		
	}
	glutPostRedisplay();
}
// Função callback para o mouse movimentado com botão pressionado
void movimento(int x, int y)
{
	if (posMouse.x < x) {
		cout << "dir" << endl;
		atribCamera.angVisao.x -= 1.0f;
	}
	else {
		cout << "esq" << endl;
		atribCamera.angVisao.x += 1.0f;
	}
	if (posMouse.y < y) {
		cout << "baixo" << endl;
		if (atribCamera.angVisao.z < 179.0) atribCamera.angVisao.z += 1.0f;
	}
	else {
		cout << "cima" << endl;
		if (atribCamera.angVisao.z > 1.00) atribCamera.angVisao.z -= 1.0f;
	}

	cout << "X: " << x << " , Y: " << y << endl;
	cout << "Ang visao X: " << atribCamera.angVisao.x << " , Ang Visao Y: " << atribCamera.angVisao.z << endl;
	atualizaPosicaoOlhos();
	glutPostRedisplay();
}
// Função callback chamada para gerenciar eventos do mouse
void gerenciaMouse(int botao, int estado, int x, int y)
{
	//Guarda as posições, para comparação posterior
	posMouse.x = x;
	posMouse.y = y;
	/*
	Teve-se de retirar essa funcionalidade, por incompatibilidade com outra função implementada
	if (botao == GLUT_LEFT_BUTTON)
		if (estado == GLUT_DOWN) {  // Zoom +
			if (atribCamera.distOlhar < 82) atribCamera.distOlhar += 1;
		}
	if (botao == GLUT_RIGHT_BUTTON)
		if (estado == GLUT_DOWN) {  // Zoom -
			if (atribCamera.distOlhar > 0) atribCamera.distOlhar -= 1;
		}
	/*
		
		/*
	if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		rx = x; ry = dimTelaPadrao.y - y;
		
	}*/
	//atribCamera.angVisao.z = (y- dimTelaPadrao.y/2.0 )/ dimTelaPadrao.y * 180 ;
	//atribCamera.angVisao.x = ( (dimTelaPadrao.y/2.0) - x ) / dimTelaPadrao.x * 180;
	//cout << "X: " << x << " , Y: " << y << endl;
	//atualizaPosicaoOlhos();
	//glutPostRedisplay();
}
/*Primitivas*/
void desenhaToro(float tMin, float tMax, float uMin, float uMax, float aMax) {
	/* Esta função foi baseada no gráfico Tubo do WinPlot:
     aMax é um percentual do círculo e varia de 0 a 1 
	 e foi utilizada apenas para testes - não compõe a cena final */
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
void desenhaCilindro(float raio, float comprimento) {
	if (texturaLigada) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, raio, raio, comprimento, 40.0, comprimento*30.0);
}
void desenhaCilindro(float raioBase, float raioTopo, float comprimento) {
	gluCylinder(quadCylinder, raioBase, raioTopo, comprimento, 40.0, comprimento * 30.0);
}
void desenhaCone(float diameter, float lenght) {
	if (texturaLigada) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, 0, lenght, 40.0, lenght*30.0);
}
void desenhaDisco(float diametroInterno, float diametroExterno) {
	gluQuadricTexture(quadCylinder, 1);
	gluDisk(quadCylinder, diametroInterno, diametroExterno, 32.0, 32.0);
}
void desenhaSemiEsfera(float raio, float deltaHorz, float deltaVert) {	
	float u1 = 0.00; float v1 = 0.00;
	float x = 0.0; float y = 0.0; float z = 0.0;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CURRENT_TEXTURE_COORDS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CURRENT_TEXTURE_COORDS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_SPHERE_MAP);
	glMatrixMode(GL_TEXTURE);
	glScalef(1.0 / 6.28, 1.00 / (3.14/2), 1.00);
	glBegin(GL_QUAD_STRIP);
	for (float u = 0.00; u < DOIS_PI; u += deltaHorz) {
		
		for (float v = MEIO_PI; v < PI; v += deltaVert) {
			u1 = u + deltaHorz;
			v1 = (v - MEIO_PI);
			x = cos(u1) * sin(v);
			y = sin(u1) * sin(v);
			z = cos(v);
			glNormal3f(x, y, z);			
			glTexCoord2f(u1, v1);
			glVertex3f(raio*x, raio*y, raio*z);
			x = cos(u) * sin(v);
			y = sin(u) * sin(v);
			z = cos(v);
			glNormal3f(x, y, z);
			glTexCoord2f(u, v1);
			glVertex3f(raio*x, raio*y, raio*z);			
		}		
	}	
	glEnd();
	glScalef(6.28, 3.14/2, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
/* Corpo do escorpião */
//Realiza o desenho do escorpiao
void desenhaEscorpiao(void) {	
	alteraTexturas(TEXTURA_PELE);		
	glPushMatrix();			
	//Desenha corpo interno de referencial:
	//desenhaElipsoide(3.00f);
	//1
	desenhaElipsoide(0.5f,0.86f,0.38f);
	giraX(-angCurvaCorpo);
	glTranslatef(0.0, -0.28f, 0.0);
	//2	
	desenhaElipsoide(0.68f, 0.98f, 0.42f);
	giraX(-angCurvaCorpo);
	glTranslatef(0.0, -0.35f, 0.0);
	//3	
	desenhaElipsoide(0.79f, 1.05f, 0.42f);
	giraX(-3.50f-angCurvaCorpo);
	glTranslatef(0.0, -0.28f, 0.0);
	//4	
	//desenhaElipsoide(0.92f, 1.18f, 0.42f);
	giraX(-3.50f-angCurvaCorpo);
	glTranslatef(0.0, -0.18f, 0.0);	
	//5
	//desenhaElipsoide(0.9f, 1.12f, 0.42f);
	giraX(-30.0f-angCurvaCorpo);
	//glTranslatef(0.0, -1.16f, 0.0);
	glTranslatef(0.0, -0.6f, 0.0);
	desenhaElipsoide(0.32, 0.43, 0.27f);
	desenhaCauda();
	glPopMatrix();
	glTranslatef(0.0, 0.576f, 0.2f);
	glPushMatrix();
	desenhaCabeca();
	desenha8Patas();	
	glPopMatrix(); 
}
void desenhaCabeca(void)
{
	glPushMatrix();	 //Salva posição da origem central (0,0,0)
	/* Desenha cabeça: */
	//Cabeça:
	//Desenha olhos:
	desenhaOlhos();
	popPush();
	//Desenha quelíceras:
	alteraTexturas(TEXTURA_QUELICERA);
	glTranslatef(abertQuelicera, 0.208f, -0.26f);
	desenhaQuelicera();
	glTranslatef(-2 * abertQuelicera, 0.0, 0.0);
	desenhaQuelicera();
	popPush();
	//Desenha "boca":	
	glTranslatef(0.0, 0.24, -0.16);
	//"Boca":
	desenhaElipsoide(0.28, 0.038, 0.056);
	//Desenha garra direita
	glTranslatef(0.248f, 0.0, 0.0);
	// Gira o apoio da garra
	glRotatef(angApoioGarra,1,1,1);
	desenhaElipsoide(0.065, 0.05, 0.05);
	desenhaGarraDir();
	popPush();
	//Desenha garra esquerda
	glTranslatef(-0.232f, 0.25f, -0.15f);
	// Gira o apoio da garra
	glRotatef(angApoioGarra, 1, -1, -1);
	desenhaElipsoide(0.065, 0.05, 0.05);
	desenhaGarraEsq();		
	glPopMatrix();
}
void desenha8Patas(void) {
	glPushMatrix();	
	desenha2Patas(1);	
	desenha2Patas(2);
	desenha2Patas(3);
	desenha2Patas(4);
	glPopMatrix();		
}
void desenha2Patas(int idPar)
{
	glPushMatrix();
	//Posiciona pata Direita
	switch (idPar) {
	case 1:
		glTranslatef(0.24f, -0.15f, -0.28f);
		break;
	case 2:
		glTranslatef(0.32f, -0.35f, -0.28f);
		break;
	case 3:
		glTranslatef(0.40f, -0.55f, -0.28f);
		break;
	case 4:
		glTranslatef(0.48f, -0.75f, -0.28f);
		break;
	}
	// Pata direita:
	glRotatef(50 + angApoioPataY, 0, 1, 0);
	glRotatef(angApoioPataZ/3.0, 0, 0, 1);
	//Gira
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	desenhaPataDir();
	popPush();
	// Faz a reflexão:
	glTranslatef(0, 0, 0);
	//desenhaEsfera(0.2);
	glScalef(-1.00f, 1.00f, 1.00f);
	//desenhaEsfera(0.2);
	//Posiciona pata esquerda
	switch (idPar) {
	case 1:
		glTranslatef(0.24f, -0.15f, -0.28f);
		break;
	case 2:
		glTranslatef(0.32f, -0.35f, -0.28f);
		break;
	case 3:
		glTranslatef(0.40f, -0.55f, -0.28f);
		break;
	case 4:
		glTranslatef(0.48f, -0.75f, -0.28f);
		break;
	}
	glRotatef(50 + angApoioPataY, 0, 1, 0);
	glRotatef(angApoioPataZ / 3.0, 0, 0, 1);
	//Gira
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	desenhaPataEsq();	
	//glScalef(1.00f, 1.00f, 1.00f);
	glPopMatrix();
}
void desenhaPataDir(void) {
	alteraTexturas(TEXTURA_PATA);
	glPushMatrix();    //Ponto de origem (fixação) da Pata   (Orig_O)	
	desenhaEsfera(dimPata.alt);
	giraX(-55);
	glTranslatef(0.0, dimPata.compr/3, 0.0);	
	//1 Primeira parte da pata (fixação ao corpo)
	desenhaElipsoide(dimPata.alt, dimPata.compr/2, dimPata.larg);	
	glTranslatef(0.0, dimPata.compr/3, 0.0);
	//Gira
	glRotatef(120+angApoioPataY * 0.11, 1.0f, 0.0f, 0.0);
	desenhaEsfera(dimPata.alt);
	glTranslatef(0.0, dimPata.compr / 1.8, 0.0);
	//2
	desenhaElipsoide(dimPata.alt, dimPata.compr/ 1.4f, dimPata.larg);
	glTranslatef(0.0f, dimPata.compr / 1.8, 0.0);
	desenhaEsfera(dimPata.alt);
	//Gira
	glRotatef(-50 + angApoioPataY * 0.11, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, dimPata.compr / 1.8, 0.0f);  //Move o ponto central para a nova posição
	//3
	desenhaElipsoide(dimPata.alt, dimPata.compr / 1.4, dimPata.larg); //Segunda parte da pata
	glTranslatef(0.0f, dimPata.compr / 1.8, 0.0);  //Move o ponto central para a Origem 2
	desenhaEsfera(dimPata.alt); //Desenha a esfera para saber onde será o ponto de origem novo
	//4
	glRotatef(-60+angApoioPataY * 0.11, 1.0f, 0.0f, 0.0f);  //Rotação vertical da pata	
	glTranslatef(0.0f, dimPata.compr / 2.0, 0.0);
	desenhaElipsoide(dimPata.alt/1.2, dimPata.compr/2.2, dimPata.larg/1.2);	 //Terceira parte da pata
	glPopMatrix();
}
void desenhaPataEsq(void) {	
	
	//Gira	
	glPushMatrix();
	desenhaPataDir();
	glPopMatrix();
}
void desenhaGarraDir(void)
{
	glPushMatrix();	
	glTranslatef(0.0, 0.133, 0.00);
	//Desenha base de apoio da garra:
	desenhaElipsoide(0.04, 0.19, 0.06);	
	glTranslatef(0.0, 0.208f, 0.00);
	///////////////////////////////////////////
	//Desenha segunda parte da garra:
	desenhaEsfera(0.07f);
	glRotatef(angMeioGarra, -1, 1, 1);
	glTranslatef(0.0, 0.25f, 0.00);
	desenhaElipsoide(0.10f, 0.28f, 0.12f);
	glTranslatef(0.0, 0.18f, 0.00);	
	glRotatef(angRotGarra, 0.00f, 1.00f, 0.00f);
	desenhaEsfera(0.1f);
	///////////////////////////////////////////
	//Inicia desenho da garra 1:			
	//alteraTexturas(TEXTURA_PATA);
	//Abertura da garra:
	giraZ(angAbertGarra+90);
	//Desenha ponta da garra 1	
	desenhaPontaGarra(1.5f * tamGarra, tamGarra, 2.5f * tamGarra);
	//popPush();
	///////////////////////////////////////////
	//Desenha garra 2:
	glTranslatef(0.0, 0.03f, 0.0f);
	giraZ(-2*angAbertGarra+180);
	//Desenha ponta da garra 2:
	glScalef(1.0f, 1.0f, -1.0f);
	desenhaPontaGarra(1.5f * tamGarra, tamGarra, 2.5f * tamGarra);
	glScalef(1.00f, 1.00f, 1.00f);		
	glPopMatrix();
}
void desenhaGarraEsq(void) {
	glScalef(-1.00f, 1.00f, 1.00f);
	desenhaGarraDir();
	//glPopMatrix();
}
void desenhaOlhos(void)
{
	//glPushMatrix();
	glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.08, 0.0, 0.065);
	desenhaEsfera(0.04);
	glTranslatef(-0.16, 0.0, 0.0);
	desenhaEsfera(0.04);	
	glPopAttrib();
	//glPopMatrix();
}
void desenhaCauda(void)
{
	glPushMatrix();	
	desenhaElipsoide(0.25, 0.35, 0.26);
	glTranslatef(0.0, -0.16, 0.0);
	//rotação vertical da cauda:
	glRotatef(angVertCauda + 15.0f, 1.0, 0.0, 0.0);
	//rotação horizontal da cauda:
	glRotatef(angHorzCauda, 0.0, 0.0, 1.0);
	//Primeira parte da cauda
	glTranslatef(0.0, -0.26, 0.0);
	desenhaElipsoide(0.18, 0.45, 0.24);
	//Segunda parte da cauda
	glTranslatef(0.0, -0.36, 0.0);
	glRotatef(angVertCauda * (pow(exp(2),(angVertCauda/256))), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.36, 0.0);
	desenhaElipsoide(0.16, 0.45, 0.22);
	//Terceira parte da cauda
	glTranslatef(0.0, -0.38, 0.0);
	glRotatef(angVertCauda * (pow(exp(4), (angVertCauda / 256))), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.38, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.16, 0.45, 0.20);
	//Quarta parte da cauda
	glTranslatef(0.0, -0.38, 0.0);
	glRotatef(angVertCauda * (pow(exp(8), (angVertCauda / 512))), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.38, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.14, 0.45, 0.18);
	//Quinta parte da cauda
	glTranslatef(0.0, -0.38, 0.0);
	glRotatef(angVertCauda * (pow(exp(8), (angVertCauda / 512))), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.38, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.12, 0.45, 0.16);
	//Ferrão da cauda
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(angVertCauda / 5 - 30, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.1, 0.0);
	desenhaElipsoide(0.0, 180.0, 0.14, 0.25, 0.16);
	//glPushMatrix();
	glRotatef(180, 0.00f, 1.00f, 0.00f);
	glRotatef(267.36f, 1.00f, 0.00f, 0.00f);
	//glTranslatef(0.0, 0.192+vTeste1, -0.12+vTeste2);
	glTranslatef(0.0, 0.032, -0.09);
	desenhaQuelicera();
	glPopMatrix();
}
void escreveSobreTrabalho(void)
{
	cout << "Trabalho final da disciplina Computacao Grafica - IME-URJ" << endl;
	cout << "Aluno: Roberto Carlos dos Santos"<< endl;
	cout << "Professor: GILSON ALEXANDRE OSTWALD PEDRO DA COSTA"<<endl;
	cout << "2018-2 (entregue em 14/01/2019)."<<endl;
}
void desenhaSetasOrientacao(void)
{	
	glPushMatrix();
	glPushAttrib(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_TEXTURE_2D);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	texto("X", 1.0, 0.0, 0.0,GLUT_BITMAP_8_BY_13);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	texto("Y", 0.0, 1.0, 0.0, GLUT_BITMAP_8_BY_13);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	texto("Z", 0.0, 0.0, 1.0, GLUT_BITMAP_8_BY_13);
	glPopAttrib();
	glPopMatrix();
}
void desenhaEsfera(float raio) {
	gluQuadricTexture(quadSphere, 1);
	gluSphere(quadSphere, raio, 32, 32);
}
void desenhaEsfera(void) {
	//Desenha esfera de raio fixo em 0.02f
	gluQuadricTexture(quadSphere, 1);
	gluSphere(quadSphere, 0.02f, 32, 32);
}
void desenhaElipsoide(float angInicial, float angFinal, float largura, float comprimento, float altura)
{	
	/* Os ângulos inicial e final variam de 0 a 180 graus */
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	angInicial = ajustaGrau(angInicial);
	angFinal = ajustaGrau(angFinal);	
	float deltaU = 0.16f;
	float deltaV = 0.1904f;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	float x = 0.00; float y = 0.00; float z = 0.00;	
	float u1 = 0.00f; float v1 = 0.00f;
	glBegin(GL_TRIANGLE_STRIP);	
	for (float u = angInicial; u <= angFinal + .0001; u += deltaU)
	{		
		//Desenha anéis:		
		for (float v = 0.0f; v <= DOIS_PI+deltaV; v += deltaV)
		{
			
			x = largura * cos(u) * cos(v);
			y = altura * cos(u) * sin(v);
			z = comprimento * sin(u);
			glNormal3f(x, y, z);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);
			//glTexCoord2f(u, v);			
			u1 = u + deltaU;
			//v1 = v + deltaV;						
			x = largura * cos(u1) * cos(v);
			y = altura * cos(u1) * sin(v);
			z = comprimento * sin(u1);
			glNormal3f(x, y, z);
			glTexCoord2f(u1, v);
			glVertex3f(x,y,z);
		}						
	}
	glEnd();
	glPopMatrix();
	glutPostRedisplay();
}
void desenhaElipsoide(float largura, float comprimento,  float altura)
{
	float angInicial = 0.0f;
	float angFinal = 180.00f;
	desenhaElipsoide(angInicial, angFinal, largura, comprimento, altura);
}
void desenhaElipsoide(float escala)
{
	float angInicial = 0.0f;
	float angFinal = 180.00f;
	float largura = 0.034f*escala;
	float comprimento = 0.075f*escala;
	float altura = 0.024f*escala;
	desenhaElipsoide(angInicial, angFinal, largura, comprimento, altura);
}
void desenhaPontaGarra(float sx, float sy, float sz) {
	glPushMatrix();	
	glTranslatef(0.0, -0.13f, -0.213f);
	glScalef(sx, sy, sz);
	//glScalef(0.12f, 0.12f, 0.12f);
	float deltaU = 0.012857f;
	float deltaV = 0.017952f;
	float fator = 1.5f;
	float x = 0.00; float y = 0.00; float z = 0.00;
	glBegin(GL_TRIANGLE_STRIP);
	float u1 = 0.00f; float v1 = 0.00f;
	for (float u = -deltaU; u < (30.00 * deltaU); u += deltaU)
	{
		//Desenha aneis:
		for (float v = -deltaV; v <= DOIS_PI; v += deltaV)
		{
			//1						
			u1 = u + deltaU;
			//v1 = v;
			x = (u1 * sin(v));
			y = ((fator + u1 * cos(v)) * sin(DOIS_PI * u1));
			z = -((fator + u1 * cos(v)) * cos(DOIS_PI * u1) + fator * u1);
			glNormal3f(x, y, z);
			glTexCoord2f(u1, v);
			glVertex3f(x, y, z);

			//2
			x = (u * sin(v));
			y = ((fator + u * cos(v))*sin(DOIS_PI * u));
			z = -((fator + u * cos(v))*cos(DOIS_PI * u) + fator * u);
			glNormal3f(x, y, z);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glPopMatrix();
	glutPostRedisplay();
}
void desenhaQuelicera(float sx, float sy, float sz) {
	glPushMatrix();
	//glRotatef(-90, 0.00f, 1.00f, 0.00f);
	//glRotatef(60, 0.00f, 0.00f, 1.00f);
	glTranslatef(0.0, -0.15f, -0.08f);
	glScalef(sx, sy, sz);
	//glScalef(0.12f, 0.12f, 0.12f);
	float deltaU = 0.012857f;
	float deltaV = 0.017952f;
	float fator = 2.4f;
	float x = 0.00; float y = 0.00; float z = 0.00;
	glBegin(GL_TRIANGLE_STRIP);
	float u1 = 0.00f; float v1 = 0.00f;
	for (float u = -deltaU; u < (30.00 * deltaU); u += deltaU)
	{
		//Desenha aneis:
		for (float v = -deltaV; v <= DOIS_PI; v += deltaV)
		{
			//1						
			u1 = u + deltaU;
			//v1 = v;
			x = (u1 * sin(v));
			y = ((fator + u1 * cos(v)) * sin(DOIS_PI * u1));
			z = -((fator + u1 * cos(v)) * cos(DOIS_PI * u1) + fator * u1);
			glNormal3f(x, y, z);
			glTexCoord2f(u1, v);
			glVertex3f(x, y, z);

			//2
			x = (u * sin(v));
			y = ((fator + u * cos(v))*sin(DOIS_PI * u));
			z = -((fator + u * cos(v))*cos(DOIS_PI * u) + fator * u);
			glNormal3f(x, y, z);
			glTexCoord2f(u, v);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glPopMatrix();
	glutPostRedisplay();
}
void desenhaQuelicera(void)
{	
	desenhaQuelicera(0.15831f, 0.059577f,  0.12155f);
}
float ajustaGrau(float angulo)
{
	// A função converte a escala de 0 a 180 graus em radianos equivalentes 
	// ao trecho: - pi/2 a pi/2
	if (angulo >= 0 && angulo < 90) {
		return -(90 - angulo)*(PI / 180);
	}
	else
	{
		return (angulo - 90)*(PI / 180);
	}
}
void atualizaPosicaoOlhos() {

	atribCamera.pos.x = atribCamera.distOlhar * cos(radiano(atribCamera.angVisao.z)) * cos(radiano(atribCamera.angVisao.x));
	atribCamera.pos.y = atribCamera.distOlhar * cos(radiano(atribCamera.angVisao.z)) * sin(radiano(atribCamera.angVisao.x));
	atribCamera.pos.z = atribCamera.distOlhar * sin(radiano(atribCamera.angVisao.z));
}
/*Cenário*/
void centralizaCena(void) {
	//Apenas para testes o parâmetro abaixo:
	vTeste1 = 0.00;
	vTeste2 = 0.00;	
	vTeste3 = 0.00;
	dbPos.x = 0.0f; dbPos.y = 0.0f; dbPos.z = 0.0f;
	ligaEsferaDebug = false;
	/*///////////////////////////*/
	contaPassgs = 0;
	dimTelaPadrao.x = 800.00f;
	dimTelaPadrao.y = 800.00f;
	raioCurvaCorpo = 1.0;
	diametroCilindro = 0.1;
	raioEsfera = 0.4;
	angCurvaCorpo = 0.0;
	angVertCauda = 0.0;
	angHorzCauda = 0.0;
	angApoioPataY = 15.0;
	angApoioPataZ = 5.0;
	angRotGarra = 0.0;
	angApoioGarra = -185.00f;
	angMeioGarra = -75.00f;
	angAbertGarra = 18.0;
	dimPata.larg = 0.07f;
	dimPata.compr = 0.42f;
	dimPata.alt = 0.04f;
	tamGarra = 0.1429f;
	altEscorpiao = 1.04f;
	abertQuelicera = 0.029;
	escalaYQuel = 0.017;
	parametrosCameras();
	angProjecao.x = 0.0f;
	angProjecao.y = 0.0f;
	atribCeu.x = 70.00;
	atribCeu.z = 0.00;
	atribCeu.raio = 80.0;
	glMatrixMode(GL_PROJECTION);
	glTranslatef(0.0, 0.0, 0.0);
	texturaLigada = true;
	desenhaEscorpiaoLig = true;
	desenhaCeuLig = true;
	desenhaPisoLig = true;
	ligaSetasOrient = true;
	abrindoQuelicera = true;
	curvandoCauda = true;
	curvandoCorpo = true;	
	abrindoGarra = true;
	fundoBrancoSim = true;
	semMovimentosAutomaticos = false;
}
void trocaCameraAtiva(void)
{
	if ((idCameraAtiva + 1) <= NUM_CAMERAS) {
		idCameraAtiva++;
	}
	else {
		idCameraAtiva = 1;
	}
	centralizaCena();
}
void alteraTexturas(int textura)
{
	if (!texturaLigada) textura = SEM_TEXTURA;
	switch (textura) {
	case SEM_TEXTURA:
		break;
	case TEXTURA_CEU:
		glBindTexture(GL_TEXTURE_2D, _textIdCeu);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TEXTURA_PATA:
		glBindTexture(GL_TEXTURE_2D, _textIdPata);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case TEXTURA_PELE:
		glBindTexture(GL_TEXTURE_2D, _textIdPele);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case TEXTURA_PISO:
		glBindTexture(GL_TEXTURE_2D, _textIdPiso);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TEXTURA_QUELICERA:
		glBindTexture(GL_TEXTURE_2D, _textIdQuelicera);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	default:
		break;
	}	
}
void desenhaCeu() {
	glPushMatrix();
	float deltaHorz = 0.03; float deltaVert = 0.03; float raio = atribCeu.raio;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.55f, 0.70f, 0.80f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade0);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture0);
	alteraTexturas(TEXTURA_CEU);
	glTranslatef(0.0f, 20.0f, 0.0);
	glRotatef(atribCeu.x, 1, 0, 0);
	glRotatef(atribCeu.z, 0, 0, 1);
	//cout << "ang X Ceu = " << atribCeu.x << " ang Z =" << atribCeu.z << endl;
	desenhaSemiEsfera(raio, deltaHorz, deltaVert);
	glColor3f(0.65f, 0.55f, 0.45f);
	glPopMatrix();
	glutPostRedisplay();
}
void desenhaPiso() {
	glPushMatrix();
	float raio = atribCeu.raio - 0.5;
	alteraTexturas(TEXTURA_PISO);
	glMatrixMode(GL_TEXTURE);
	glScalef(20.00, 20.00, 1);
	desenhaDisco(0.00, raio);
	glScalef(1/20.00, 1/20.00, 1);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
void redimVisao(int w, int h) {
	/* Redimensiona a tela e altera o modo de projeção */
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int idCam = idCameraAtiva;
	switch (idCam){
		case 1:   //Visão perspectiva
			gluPerspective(60.0, (float)w / (float)h, 0.0001f, 80.0f);
			cout << "Modo de visão: perspectiva" << endl;
			break;
		case 2:   //Visão perspectiva
			gluPerspective(120.0, (float)w / (float)h, 0.0001f, 90.0f);
			cout << "Modo de visão: perspectiva" << endl;
			break;
		case 3:   //Visão ortogonal
			glOrtho(-8.0f, 8.0f, -8.0f, 8.0f, -80.0f, 80.0f);
			cout << "Modo de visão: ortogonal" << endl;
			break;
		case 4:    //Visão frustum
			glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 82.0f);
			cout << "Modo de visão: frustum" << endl;
			break;
		default:
			gluPerspective(60.0, (float)w / (float)h, 0.0001, 80.0);			
			cout << "Modo de visão: default (perspectiva)" << endl;
			break;
	}
	
}
void parametrosIluminacao(void)
{
	if (texturaLigada) {
		glEnable(GL_COLOR_MATERIAL);
		//Luzes
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
		glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
		glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);

		// Inicializa cores e parâmetros	
		glMateriali(GL_FRONT, GL_SHININESS, 1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade0);
		glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture0);

		glColor3f(0.65f, 0.55f, 0.45f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade1);
		glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture1);
	}
	else {
		glDisable(GL_COLOR_MATERIAL);
		glColor3f(1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especulrdadeTexturaDeslg);
		glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexturaDeslg);
	}

	//Cor do fundo (a ser vista apenas com os cenários de frente desligados)
	if (fundoBrancoSim) {
		// Especifica que a cor de fundo da janela será branca
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		// Especifica que a cor de fundo da janela será preta
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
//Realiza o desenho da cena
void desenhaCenaTestes(void) {
	//Este procedimento serviu apenas para depuração e testes do programa.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	if (atribCamera.angVisao.z < 90) {
		atribCamera.angInclin.z = 1.00;
	}
	else {
		atribCamera.angInclin.z = -1.00;
	}*/
	gluLookAt(atribCamera.pos.x, atribCamera.pos.y, atribCamera.pos.z,
		atribCamera.foco.x, atribCamera.foco.y, atribCamera.foco.z,
		atribCamera.angInclin.x, atribCamera.angInclin.y, atribCamera.angInclin.z);

	if (ligaWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	parametrosIluminacao();
	//glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0, 0.0, 0.0);
	//Desenha setas de orientação:
	if (ligaSetasOrient) desenhaSetasOrientacao();

	glPushMatrix();
	alteraTexturas(TEXTURA_PELE);
	//desenhaGarraDir();
	//desenhaQuelicera();
	//desenhaCauda();
	//desenhaCabeca();
	//desenhaEscorpiao();
	//desenhaElipsoide(2.05f);
	//desenhaPontaGarra(0.2143, 0.1429, 0.3571);
	//desenhaPataDir();
	desenhaCauda();
	glTranslatef(0, 0, 0);
	if (ligaEsferaDebug) informaPosicao();
	glPopMatrix();
	//glScalef(2.0, 0.5, 1.0);
	/*
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.5, 1, 0);
	glutSolidCube(0.1);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(1.0, 0.0, 0.0, 1, 0, 0, 0, 0, 1);
	glPushMatrix(); // save camera matrix
	glutSolidCube(0.1);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(0.2);
	glPopMatrix(); // get camera matrix	
	glTranslatef(0.5, 0, 0);
	glutSolidCube(0.1);
	gluLookAt(1.0, 0.0, 0.0, 1,0,0,0,0,1);
	glutSolidCube(0.1);
	gluLookAt(1.0, 0.0, 0.0, 2, 0, 0, 0, 0, 1);
	glutSolidCube(0.1);
	glPopMatrix();

	/* -------------------------------
	//Abaixo apenas para testes
	desenhaPataDir();

	glColor3f(1.0f, 1.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade1);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterialTexture1);

	/* Trecho final dos testes */

	// desenha o piso:
	//if (desenhaPisoLig) desenhaPiso();

	//glTranslatef(0.0, 0.0, -altEscorpiao);
	// desenha o céu
	//if (desenhaCeuLig) desenhaCeu();

	//vTeste1 += 3;
	//giraZ(vTeste1);

	//glTranslatef(0, 0, 0);

	/* As linhas de baixo dão a sensação de mundo girando*/
	//glMatrixMode(GL_PROJECTION);
	//glRotatef(angProjecao.x, 1.0, 0, 0);
	//glRotatef(angProjecao.y, 0, 1.0, 0);	
	//A linha de baixo serviu apenas para teste de escrita de texto:
	//texto("Roberto", 0.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24);

	glutSwapBuffers();
}
void desenhaCena(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	//Posicionamento da câmera:
	gluLookAt(atribCamera.pos.x, atribCamera.pos.y, atribCamera.pos.z, 
		atribCamera.foco.x, atribCamera.foco.y, atribCamera.foco.z,		
		atribCamera.angInclin.x, atribCamera.angInclin.y, atribCamera.angInclin.z);
		
	//Liga ou desliga o WireFrame (linhas de construção dos elementos da imagem):
	if (ligaWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (texturaLigada) glEnable(GL_TEXTURE_2D); else glColor3f(0.20, 0.20, 0.20);
	
	//Configuração das luzes:
	parametrosIluminacao();

	glTranslatef(0.0,0.0,0.0);

	//Desenha setas de orientação:
	if (ligaSetasOrient) desenhaSetasOrientacao();
		
	//desenha o piso:
	if (desenhaPisoLig) desenhaPiso();

	glTranslatef(0.0, 0.0, 0.0);

	// desenha o céu
	if (desenhaCeuLig) desenhaCeu();
	
	//Desenha o primeiro escorpião:
	glTranslatef(0.0, -2.0f, altEscorpiao);	
	if (desenhaEscorpiaoLig) desenhaEscorpiao();

	glColor3f(0.25,0.35,0.45);
	//Reflexão (um escorpião em frente ao outro)
	glScalef(1.00f, -1.00f, 1.00f);

	glTranslatef(0.0, -3.0f, -0.2);

	//Desenha o segundo escorpião
	if (desenhaEscorpiaoLig) desenhaEscorpiao();
	//glPopMatrix();

	glScalef(1.00f, 1.00f, 1.00f);

	//glTranslatef(0, 0, 0);

	if (ligaEsferaDebug) informaPosicao();

	if (texturaLigada)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}
void informaPosicao(void)
{   
	glMatrixMode(GL_COLOR);
	glPushMatrix();
	verde();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(dbPos.x, dbPos.y, dbPos.z);
	desenhaEsfera(0.012);
	glPopMatrix();
	glMatrixMode(GL_COLOR);
	glPopMatrix();
	cout << "X: "<< dbPos.x << "Y: "<< dbPos.y << "Z: " << dbPos.z << endl;
}
void atualizaMovimentosAutomaticos(void) {
	contaPassgs++;
	if (semMovimentosAutomaticos) return;
	//Atualiza o movimento das quelíceras
	if (abrindoQuelicera) {
		if (abertQuelicera < 0.066) {
			abertQuelicera += 0.0017;
			escalaYQuel += 0.0001;
		} else {
			abrindoQuelicera = false;
		}
	}
	else {
		if (abertQuelicera > 0.026) {
			abertQuelicera -= 0.0017;
			escalaYQuel -= 0.0001;
		}
		else {
			abrindoQuelicera = true;
		}
	}
	
	//Atualiza o movimento do corpo	
	if (curvandoCorpo) {
		if (angCurvaCorpo < 6.50f) {
			angCurvaCorpo += 0.08;
			//Altura do escorpião:
			if (angApoioPataY > -15.00f) {
				angApoioPataY -= 1;
				altEscorpiao -= 0.0095f;
			}
			//Reduz o ângulo de apoio da Pata em Z
			if (angApoioPataZ >= -35.00f) angApoioPataZ -= 4;

			//Aumenta angulo do meio da garra
			if (angMeioGarra > -180.0f) angMeioGarra -= 1.5;

			//Reduz o ângulo de apoio da garra
			if (angApoioGarra > -180) angApoioGarra -= 3;

		}
		else {
			curvandoCorpo = false;
		}
	}
	else {
		if (angCurvaCorpo > -5.20f) {
			angCurvaCorpo -= 0.08;
			//Altura do escorpiao
			if (angApoioPataY < 20.00f) {
				angApoioPataY += 1;
				altEscorpiao += 0.0095f;
			}
			//Aumenta o ângulo de apoio da Pata em Z
			if (angApoioPataZ <= 35.00f) angApoioPataZ += 4;

			//Aumenta angulo do meio da garra
			if (angMeioGarra < 50.0f) angMeioGarra += 1.5;

			//Aumenta o ângulo de apoio da garra
			if (angApoioGarra < 180) angApoioGarra += 3;
		}
		else {
			curvandoCorpo = true;
		}
	} 
	/*
	if (curvandoCorpo) {
		if (raioCurvaCorpo < 100.0f) {
			raioCurvaCorpo += 5.00f;
		}
		else {
			curvandoCorpo = false;
		}
	}
	else {
		if (raioCurvaCorpo > 5.00f) {
			raioCurvaCorpo -= 5.00f;
		}
		else {
			curvandoCorpo = true;
		}
	}*/
	// Rotação do céu
	if (contaPassgs % 16 == 0) {
		atribCeu.z -= 2.5;
		contaPassgs = 0;
	}
	//Atualiza o movimento da cauda	
	if (curvandoCauda) {
		if (angHorzCauda < 45.00) {
			angHorzCauda += 0.8;
		}
		else {
			curvandoCauda = false;
		}
	}
	else {
		if (angHorzCauda > -45.0) {
			angHorzCauda -= 0.8;
		}
		else {
			curvandoCauda = true;
		}
	}
	
	if (angCurvaCorpo > 2.76f) angVertCauda = -8 * angCurvaCorpo;

	//Atualiza abre e fecha das garras
	if (abrindoGarra) {
		if (angAbertGarra < 35) {
			angAbertGarra += 3;
		}
		else {
			abrindoGarra = false;
		}
	}
	else {
		if (angAbertGarra > 10) {
			angAbertGarra -= 3;
		}
		else {
			abrindoGarra = true;
		}
	}

	//Roda a projeção do cenário:
	atribCamera.angVisao.x += 1.0f;
	atualizaPosicaoOlhos();	
}

int main(int argc, char** argv) {
	escreveSobreTrabalho();
	glutInit(&argc, argv);
	texturaLigada = true;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(dimTelaPadrao.x,dimTelaPadrao.y);
	glutCreateWindow("Escorpião");
	inicializaIluminacao();
	inicializaRenderizacao();
	glutDisplayFunc(desenhaCena);
	//glutDisplayFunc(desenhaCenaTestes);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(tecladoFuncoesEspeciais);
	glutMotionFunc(movimento);
	glutMouseFunc(gerenciaMouse);
	glutReshapeFunc(redimVisao);
	glutIdleFunc(atualizaMovimentosAutomaticos);
	glutMainLoop();
	escreveSobreTrabalho();
	return 0;
}