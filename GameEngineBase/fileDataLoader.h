#ifndef _FILEDATA_LOADER_H
#define _FILEDATA_LOADER_H

//#include "global.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glew.h>
#include <vector>
#include "mediator.h"
#include "Vector3D.h"

#include "shaderUniformVariables.h"


void ExitOnGLError(const char* error_message);

class FileDataLoader
{
public:
	FileDataLoader();
	~FileDataLoader();
	
	void loadXML(std::string fileName, std::string rootNode,GameMediator* mediator ,  CShaderUniformVariables &g_ShaderUniformVariables);
	void saveXML();

	void loadTexture(GameMediator* mediator);

	static GLuint LoadShader(const char* filename, GLenum shader_type);

	std::wstring ASCII_to_Unicode( std::string ASCIIstring );

private:
	//std::vector< std::string > vecModelsToLoad;
	std::string modelname;
	std::string plypath;
	std::string temp1, temp2, temp3, physics;
	int textureIndex;
	int altTextureIndex;
	std::string texturePath;
	Vector3D position;
	Vector3D rotation;
	float scale,player;
	float colr, colg, colb;

};


#endif