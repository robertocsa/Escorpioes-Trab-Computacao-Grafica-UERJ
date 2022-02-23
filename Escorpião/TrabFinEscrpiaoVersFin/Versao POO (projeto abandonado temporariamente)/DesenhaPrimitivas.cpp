/*DesenhaPrimitivas.h 
Classe para os desenhos mais básicos e gerais como o de esferas, cilíndros, elipsóides etc
Todas as funções dessa classe são estáticas, portanto, não existe o arquivo CPP correspondente
*/

#include "DesenhaPrimitivas.h"

using namespace std;

DesenhaPrimitivas::DesenhaPrimitivas()
{
}
DesenhaPrimitivas::~DesenhaPrimitivas()
{
}

// Insere a imagem em uma textura e retorna o id da textura
GLuint DesenhaPrimitivas::loadTexture(char *filename) {

	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
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
