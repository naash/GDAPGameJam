#ifndef _SHADER_CLASS
#define _SHADER_CLASS

#include <map>
#include <string>
#include <glew.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


//To pack data while setting uniform varaibles
struct UniformData
{
	int intData;
	float floatData;
	float float3Data[3];
	float float4Data[4];
	bool boolData;

	//Need 3 variables for texture 
	GLuint textureNumData;   //To set uniform
	GLuint textureCodeData;   //To activate
	GLuint textureBindData;   //To bind

	//GLU variables
	glm::mat4 mat4Data;
	glm::mat3 mat3Data;
	glm::mat2 mat2Data;
	glm::vec3 vec3Data;
	glm::vec4 vec4Data;
};

enum UniformType
{
	UNIMAT2,
	UNIMAT3,
	UNIMAT4,
	UNIINT,
	UNIBOOL,
	UNIFLOAT1,
	UNIFLOAT2,
	UNIFLOAT3,
	UNIFLOAT4,
	UNITEXTURE,
	UNISKY,
};

class Shader
{
	public:
		Shader(std::string name);
		~Shader();
		void addShader(GLenum type, std::string path);
		void addUniformVariables( std::map<std::string, UniformType> &uniformVarType);
		void setUniformVariablesInBulk(std::map<std::string , UniformData> &uniformData, bool offScreen = false);   //Bulk setting of uniform vairables
		void setUniformVariable(std::string uniformName, UniformData &uniformData, bool offScreen);   //Single setting
		void linkShader();
		void enableShader();
		GLuint getProgramID();
	private:
		std::string shaderName; //To identify shader
		GLuint programId;
		std::map<GLenum,int> shaderList;
		std::map<std::string , int> uniformList;
		std::map<std::string, UniformType> uniformVarType;
		
};

#endif