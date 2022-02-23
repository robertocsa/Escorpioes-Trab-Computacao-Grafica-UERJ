// Cameras.cpp :  
/* Classe para controle de objetos camera */

using namespace std;

#include "Cameras.h"
#include <iostream>

/*////////////////////////////////////////////////////////////////////////////////////*/
// "Camera.cpp" :  
/*Classe Camera*/
/* Classe para criação e posicionamento de objetos camera */
Camera::Camera() {
	int idCamera = Cameras::obtemNovoId();
	this->configAtribPadrao(idCamera);
}
Camera::Camera(int idCamera)
{
	this->atrib.id = idCamera;
	this->atrib.ativa = true;
	this->atrib.distOlhar = 10;
	this->atrib.foco.x = 0.00; this->atrib.foco.y = 0.00; this->atrib.foco.z = 1.00;
	this->atrib.pos.x = 0.00; this->atrib.pos.y = 0.00; this->atrib.pos.z = 10.00;
	this->atrib.angVisao.x = 30; this->atrib.angVisao.z = 30;
}
Camera::Camera(_camera _camera) {
	_camera.ativa = true;
	_camera.distOlhar = 10;
	this->alteraAtributos(_camera);
}
void Camera::configAtribPadrao(int idCamera) {
	_camera atrib;
	atrib.id = idCamera;
	atrib.ativa = true;
	atrib.angVisao.x = 30;
	atrib.angVisao.z = 30;
	atrib.distOlhar = 10;
	atrib.foco.x = 0.00;
	atrib.foco.y = 0.00;
	atrib.foco.z = 1.00;
	atrib.pos.x = 0.00;
	atrib.pos.y = 0.00;
	atrib.pos.z = 1.00;
	this->alteraAtributos(atrib);
}
void Camera::atualizaMovimentosAutomaticos(void) {
	//Atualiza o movimento da camera
	_camera camAtual = this->atrib;
	if (camAtual.angVisao.z < 90)
		gluLookAt(camAtual.foco.x, camAtual.foco.y, camAtual.foco.z, 
			camAtual.pos.x, camAtual.pos.y, camAtual.pos.z, 0.0, 0.0, 1.0);
	else
		gluLookAt(camAtual.foco.x, camAtual.foco.y, camAtual.foco.z,
			camAtual.pos.x, camAtual.pos.y, camAtual.pos.z, 0.0, 0.0, -1.0);
}
bool Camera::obtemEstadoAtivo(void)
{
	return this->atrib.ativa;
}
void Camera::alteraEstadoAtivo(bool estaAtiva)
{
	this->atrib.ativa = estaAtiva;
}
int Camera::obtemIdCamera(void)
{
	return this->atrib.id;
}

_camera Camera::obtemAtributos(void)
{
	return this->atrib;
}

void Camera::alteraAtributos(_camera atributos)
{
	this->atrib = atributos;
}
