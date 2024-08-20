#include "shaderClass.h"
#include "fileDataLoader.h"

Shader::Shader(std::string name)
{
	programId =  glCreateProgram();	
	this->shaderName = name;
}

Shader::~Shader()
{

}

void Shader::addShader(GLenum type, std::string path)
{

	shaderList[type] = FileDataLoader::LoadShader(path.c_str(), type);

	glAttachShader( programId, shaderList[type] );
	
}

void Shader::linkShader()
{
	glLinkProgram( programId );
	ExitOnGLError("error while linking");
}


void Shader::enableShader()
{
	glUseProgram(programId);
}


GLuint Shader::getProgramID()
{
	return programId;
}

void Shader::addUniformVariables( std::map<std::string, UniformType> &p_type)
{

	

	//Adds  type
	for(std::map<std::string, UniformType>::iterator mapIter = p_type.begin();mapIter != p_type.end(); mapIter++)
	{
		this->uniformVarType[mapIter->first] =  mapIter->second;		
		this->uniformList[mapIter->first] = 0;
	}


	
	//Get their location
	for(std::map<std::string , int>::iterator mapIter = this->uniformList.begin();mapIter != this->uniformList.end(); mapIter++)
	{
		mapIter->second = glGetUniformLocation( programId, (mapIter->first).c_str());
		if ( mapIter->second == -1 )
		{
			std::cout << "Warning: Can't find "<<mapIter->first<<" uniform variable in shader program." << std::endl;
		}

	}
	

}



void Shader::setUniformVariablesInBulk(std::map<std::string , UniformData> &uniformData, bool offScreen)
{
	for(std::map<std::string , UniformData>::iterator mapIter = uniformData.begin();mapIter != uniformData.end(); mapIter++)
	{
		this->setUniformVariable(mapIter->first, mapIter->second, offScreen);
	}
}


void Shader::setUniformVariable(std::string uniformName, UniformData &uniformData,bool offScreen)
{
	/*
	Check type ... based on that set unifrom variables
	*/
	if(this->uniformVarType[uniformName] == UNIINT)
	{
		glUniform1i(this->uniformList[uniformName], uniformData.intData);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNIFLOAT1)
	{
		glUniform1f(this->uniformList[uniformName], uniformData.floatData);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNIFLOAT3)
	{
		glUniform3f(this->uniformList[uniformName], uniformData.float3Data[0],uniformData.float3Data[1],uniformData.float3Data[2]);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNIFLOAT4)
	{
		glUniform4f(this->uniformList[uniformName], uniformData.float4Data[0],uniformData.float4Data[1],uniformData.float4Data[2], uniformData.float4Data[3]);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNIBOOL)
	{
		glUniform1i(this->uniformList[uniformName], uniformData.boolData);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNISKY)
	{
		glUniform1i(this->uniformList[uniformName], uniformData.textureNumData);
		glActiveTexture(uniformData.textureCodeData);

		glDisable( GL_CULL_FACE );	// Turn on culling

		glBindTexture(GL_TEXTURE_CUBE_MAP, uniformData.textureBindData);
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNITEXTURE)
	{
		//
		if(!offScreen)
		{
			glActiveTexture(uniformData.textureCodeData);
		}

		glBindTexture(GL_TEXTURE_2D, uniformData.textureBindData);
		glUniform1i(this->uniformList[uniformName], uniformData.textureNumData);
	

		glEnable( GL_CULL_FACE );	// Turn on culling

		
		ExitOnGLError(uniformName.c_str());
	}
	else if(this->uniformVarType[uniformName] == UNIMAT4)
	{
		glUniformMatrix4fv(this->uniformList[uniformName], 1, GL_FALSE, glm::value_ptr(uniformData.mat4Data));
		ExitOnGLError(uniformName.c_str());
	}

}
