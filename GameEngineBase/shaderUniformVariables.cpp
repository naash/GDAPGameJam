#include "global.h"

#include <vector>
#include <fstream>
#include <iostream>	// for printing out error messages
#include <sstream>  // For the SetLightingUniforms() function

// Note: this file used to be called LoadPlyFileIntoGLBuffers

bool SetLightingUniforms(GLuint programId);


bool g_SetShaderUniformVariables(GLuint programId)
{
	

	// ***********************************************************************************
	// ********************************* TOP SECRET CODE *********************************
	if ( !SetLightingUniforms(programId) )
	{
		std::cout << "Warning: Can't find (one or more) Lights uniform variable in shader program." << std::endl;
	}		

	
	ExitOnGLError("ERROR: Could not get shader uniform locations");

	return true;
}

// Note: this entire thing can be replaced by a different type of buffer (which we'll talk about later in the course)
bool SetLightingUniforms(GLuint programId)
{
	bool bNoErrors = true;

	std::string isEnabled;
	std::string isLocal;
	std::string isSpot;
	std::string ambient;
	std::string color;
	std::string position;
	std::string halfVector;
	std::string coneDirection;
	std::string spotCosCutoff;
	std::string spotExponent;
	std::string constantAttenuation;
	std::string linearAttenuation;
	std::string quadraticAttenuation;
	for (int i = 0; i < ::g_ShaderUniformVariables.MaxLights; i++)
	{
	

	isEnabled = "Lights[" + std::to_string(i) +"].isEnabled";
	isLocal = "Lights[" + std::to_string(i) + "].isLocal";
	isSpot = "Lights[" + std::to_string(i) + "].isSpot";
	ambient = "Lights[" + std::to_string(i) + "].ambient";
	color = "Lights[" + std::to_string(i) + "].color";
	position = "Lights[" + std::to_string(i) +  "].position";
	halfVector = "Lights[" + std::to_string(i) + "].halfVector";
	coneDirection = "Lights[" + std::to_string(i) +"].coneDirection";
	spotCosCutoff ="Lights[" + std::to_string(i) +"].spotCosCutoff";
	spotExponent = "Lights[" + std::to_string(i) + "].spotExponent";
	constantAttenuation = "Lights[" + std::to_string(i) + "].constantAttenuation";
	linearAttenuation = "Lights[" + std::to_string(i) + "].linearAttenuation";
	quadraticAttenuation = "Lights[" + std::to_string(i) + "].quadraticAttenuation";

	const GLchar*  gl_enabled = isEnabled.c_str();
	const GLchar*  gl_Local = isLocal.c_str();
	const GLchar*  gl_Spot = isSpot.c_str();
	const GLchar*  gl_ambient = ambient.c_str();
	const GLchar*  gl_color = color.c_str();
	const GLchar*  gl_position = position.c_str();
	const GLchar*  gl_halfVector = halfVector.c_str();
	const GLchar*  gl_coneDirection = coneDirection.c_str();
	const GLchar*  gl_spotCosCutoff = spotCosCutoff.c_str();
	const GLchar*  gl_spotExponent = spotExponent.c_str();
	const GLchar*  gl_constantAttenuation = constantAttenuation.c_str();
	const GLchar*  gl_linearAttenuation = linearAttenuation.c_str();
	const GLchar*  gl_quadraticAttenuation = quadraticAttenuation.c_str();

	::g_ShaderUniformVariables.Lights[i].isEnabled_LocID = glGetUniformLocation(programId, gl_enabled);
	::g_ShaderUniformVariables.Lights[i].isLocal_LocID = glGetUniformLocation(programId, gl_Local);
	::g_ShaderUniformVariables.Lights[i].isSpot_LocID = glGetUniformLocation(programId, gl_Spot);
	::g_ShaderUniformVariables.Lights[i].ambient_LocID = glGetUniformLocation(programId, gl_ambient);
	::g_ShaderUniformVariables.Lights[i].color_LocID = glGetUniformLocation(programId, gl_color);
	::g_ShaderUniformVariables.Lights[i].position_LocID = glGetUniformLocation(programId, gl_position);
	::g_ShaderUniformVariables.Lights[i].halfVector_LocID = glGetUniformLocation(programId, gl_halfVector);
	::g_ShaderUniformVariables.Lights[i].coneDirection_LocID = glGetUniformLocation(programId, gl_coneDirection);
	::g_ShaderUniformVariables.Lights[i].spotCosCutoff_LocID = glGetUniformLocation(programId, gl_spotCosCutoff);
	::g_ShaderUniformVariables.Lights[i].spotExponent_LocID = glGetUniformLocation(programId, gl_spotExponent);
	::g_ShaderUniformVariables.Lights[i].constantAttenuation_LocID = glGetUniformLocation(programId, gl_constantAttenuation);
	::g_ShaderUniformVariables.Lights[i].linearAttenuation_LocID = glGetUniformLocation(programId, gl_linearAttenuation);
	::g_ShaderUniformVariables.Lights[i].quadraticAttenuation_LocID = glGetUniformLocation(programId, gl_quadraticAttenuation);
	



	}

	return bNoErrors;
}