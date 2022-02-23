/* Cameras.h*/
/* Classe para controle dos objetos camera */
#pragma once
#include <iostream>
#include "DesenhaPrimitivas.h"
#include "Constantes.h"

using namespace std;
using namespace nsConstantes;

/* "Camera.h"
	Classe para criação e posicionamento de objetos cameras */

class Camera {
public:
	//Construtor:
	Camera();
	Camera(int idCamera);
	Camera(_camera _camera);
	void configAtribPadrao(int camera);
	void atualizaMovimentosAutomaticos(void);
	bool obtemEstadoAtivo(void);
	void alteraEstadoAtivo(bool estadoAtividade);
	int obtemIdCamera(void);
	_camera obtemAtributos(void);
	void alteraAtributos(_camera atributos);
	//Destrutor:
	~Camera() {
		std::cout << "Chamada ao destrutor do objeto câmara de id:" << this->atrib.id << std::endl;
	}
private:
	_camera atrib;
};

/*//////////////////////////////////////////////////////////////////////////////////*/

/*Classe Cameras */

class Cameras {
public:
	//Construtor:
	Cameras() {
		this->criaNovaCamera();
	}
	//Statics:
	static int obtemNovoId(void)
	{
		int i = 0;
		for (i = 1; i < 7; i++) {
			if (listaCameras == NULL) {
				return i;
			}
		}
		return 0;
	}		
	static int obtemIdCameraAtiva(void)
	{
		return idCameraAtiva;
	}
	static Camera obtemObjCameraAtiva(void) {
		return listaCameras[idCameraAtiva];
	}
	static void atualizaMovimentosAutomaticos(void) {
		//Atualiza a automação da troca de cameras
	}
	static void atualizaPosicaoOlhos() {
		Camera objCamera = obtemObjCameraAtiva();
		_camera atrib = objCamera.obtemAtributos();
		float angVisaoX = radiano(atrib.angVisao.x);
		float angVisaoZ = radiano(atrib.angVisao.z);
		float distOlhar = atrib.distOlhar;
		atrib.foco.x = atrib.distOlhar * cos(angVisaoZ) * cos(angVisaoX);
		atrib.foco.y = distOlhar * cos(angVisaoZ) * sin(angVisaoX);
		atrib.foco.z = distOlhar * sin(angVisaoZ);
		objCamera.alteraAtributos(atrib);
	}
	static Camera criaNovaCamera(void)
	{
		int idNovaCamera = obtemNovoId();
		if (idNovaCamera != 0) {
			listaCameras[idNovaCamera] = Camera(idNovaCamera);
			return listaCameras[idNovaCamera];
		}
		return NULL;
	}
	static void alteraCameraAtiva(int cameraAtiva)
	{
		idCameraAtiva = cameraAtiva;
	}
	static void encerraCamera(int camera)
	{
		int outraCamera = existeOutraCamera(camera);
		if (outraCamera != 0) {
			encerraCamera(camera);
		}
		else {
			cout << "Impossível encerrar câmera " << camera << ". Não há outra câmera em uso" << endl;
		}
	}
	static int existeOutraCamera(int camera) {
		int i = 0;
		for (i = 0; i < 7; i++) {
			if (listaCameras[i].obtemIdCamera() != 0 &&
				listaCameras[i].obtemIdCamera() != camera) {
				return i;
			}
		}
		return 0;
	}
private:
	static int idCameraAtiva;
	static Camera listaCameras[NUM_CAMERAS];
};