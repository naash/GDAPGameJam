#include "global.h"

#include <vector>
#include <fstream>
#include <iostream>	// for printing out error messages
#include <sstream>  // For the SetLightingUniforms() function

// Note: this file used to be called LoadPlyFileIntoGLBuffers

bool SetLightingUniforms(void);


bool g_SetShaderUniformVariables(void)
{
	// From the vertex shader
	::g_ShaderUniformVariables.matWorld_LocationID 
		= glGetUniformLocation( g_ShaderProgram_ID, "WorldMatrix");
	if ( ::g_ShaderUniformVariables.matWorld_LocationID == -1 )
	{
		std::cout << "Warning: Can't find WorldMatrix uniform variable in shader program." << std::endl;
	}
	ExitOnGLError("ERROR: Could not get shader uniform locations");

	::g_ShaderUniformVariables.matView_LocationID = glGetUniformLocation(g_ShaderProgram_ID, "ViewMatrix");
	if ( ::g_ShaderUniformVariables.matView_LocationID == -1 )
	{
		std::cout << "Warning: Can't find ViewMatrix uniform variable in shader program." << std::endl;
	}

	::g_ShaderUniformVariables.matProjection_LocationID = glGetUniformLocation(g_ShaderProgram_ID, "ProjectionMatrix");
	if ( ::g_ShaderUniformVariables.matProjection_LocationID == -1 )
	{
		std::cout << "Warning: Can't find ProjectionMatrix uniform variable in shader program." << std::endl;
	}

	// From the Fragment shader
	::g_ShaderUniformVariables.Shininess_LocationID 
		= glGetUniformLocation(g_ShaderProgram_ID, "Shininess");
	if ( ::g_ShaderUniformVariables.matProjection_LocationID == -1 )
	{
		std::cout << "Warning: Can't find Shininess uniform variable in shader program." << std::endl;
	}	

	::g_ShaderUniformVariables.Strength_LocationID = glGetUniformLocation(g_ShaderProgram_ID, "Shininess");
	if ( ::g_ShaderUniformVariables.Strength_LocationID == -1 )
	{
		std::cout << "Warning: Can't find Shininess uniform variable in shader program." << std::endl;
	}	


	::g_ShaderUniformVariables.EyeDirection_LocationID = glGetUniformLocation(g_ShaderProgram_ID, "EyeDirection");
	if ( ::g_ShaderUniformVariables.EyeDirection_LocationID == -1 )
	{
		std::cout << "Warning: Can't find EyeDirection uniform variable in shader program." << std::endl;
	}		
	

	// ***********************************************************************************
	// ********************************* TOP SECRET CODE *********************************
	if ( !SetLightingUniforms() )
	{
		std::cout << "Warning: Can't find (one or more) Lights uniform variable in shader program." << std::endl;
	}		
	// ********************************* TOP SECRET CODE *********************************
	// ***********************************************************************************


	// Added on September 29. 
	// Ask OpenGL the location of our uniform variable.
	//g_ObjectColourUniformLocation = glGetUniformLocation( g_ShaderProgram_ID, "objectColour" );

	////g_slot_LightPosition = glGetUniformLocation( g_ShaderIds[0], "LightPosition" );//uniform vec4 LightPosition;
	//g_slot_LightPosition = glGetUniformLocation( g_ShaderProgram_ID, "LightPosition" );//uniform vec4 LightPosition;
	////g_slot_LightColour   = glGetUniformLocation( g_ShaderIds[0], "LightColour" );	 //uniform vec4 LightColour; 
	//g_slot_LightColour   = glGetUniformLocation( g_ShaderProgram_ID, "LightColour" );	 //uniform vec4 LightColour; 
	////g_slot_attenuation   = glGetUniformLocation( g_ShaderIds[0], "attenuation" );  //uniform float attenuation;
	//g_slot_attenuation   = glGetUniformLocation( g_ShaderProgram_ID, "attenuation" );  //uniform float attenuation;
	ExitOnGLError("ERROR: Could not get shader uniform locations");

	return true;
}

// Note: this entire thing can be replaced by a different type of buffer (which we'll talk about later in the course)
bool SetLightingUniforms(void)
{
	bool bNoErrors = true;

	::g_ShaderUniformVariables.Lights[0].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].isEnabled");
	::g_ShaderUniformVariables.Lights[0].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].isLocal");
	::g_ShaderUniformVariables.Lights[0].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].isSpot");
	::g_ShaderUniformVariables.Lights[0].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].ambient");
	::g_ShaderUniformVariables.Lights[0].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].color");
	::g_ShaderUniformVariables.Lights[0].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].position");
	::g_ShaderUniformVariables.Lights[0].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].halfVector");
	::g_ShaderUniformVariables.Lights[0].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].coneDirection");
	::g_ShaderUniformVariables.Lights[0].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[0].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].spotExponent");
	::g_ShaderUniformVariables.Lights[0].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].constantAttenuation");
	::g_ShaderUniformVariables.Lights[0].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].linearAttenuation");
	::g_ShaderUniformVariables.Lights[0].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[0].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[1].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].isEnabled");
	::g_ShaderUniformVariables.Lights[1].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].isLocal");
	::g_ShaderUniformVariables.Lights[1].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].isSpot");
	::g_ShaderUniformVariables.Lights[1].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].ambient");
	::g_ShaderUniformVariables.Lights[1].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].color");
	::g_ShaderUniformVariables.Lights[1].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].position");
	::g_ShaderUniformVariables.Lights[1].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].halfVector");
	::g_ShaderUniformVariables.Lights[1].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].coneDirection");
	::g_ShaderUniformVariables.Lights[1].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[1].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].spotExponent");
	::g_ShaderUniformVariables.Lights[1].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].constantAttenuation");
	::g_ShaderUniformVariables.Lights[1].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].linearAttenuation");
	::g_ShaderUniformVariables.Lights[1].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[1].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[2].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].isEnabled");
	::g_ShaderUniformVariables.Lights[2].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].isLocal");
	::g_ShaderUniformVariables.Lights[2].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].isSpot");
	::g_ShaderUniformVariables.Lights[2].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].ambient");
	::g_ShaderUniformVariables.Lights[2].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].color");
	::g_ShaderUniformVariables.Lights[2].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].position");
	::g_ShaderUniformVariables.Lights[2].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].halfVector");
	::g_ShaderUniformVariables.Lights[2].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].coneDirection");
	::g_ShaderUniformVariables.Lights[2].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[2].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].spotExponent");
	::g_ShaderUniformVariables.Lights[2].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].constantAttenuation");
	::g_ShaderUniformVariables.Lights[2].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].linearAttenuation");
	::g_ShaderUniformVariables.Lights[2].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[2].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[3].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].isEnabled");
	::g_ShaderUniformVariables.Lights[3].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].isLocal");
	::g_ShaderUniformVariables.Lights[3].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].isSpot");
	::g_ShaderUniformVariables.Lights[3].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].ambient");
	::g_ShaderUniformVariables.Lights[3].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].color");
	::g_ShaderUniformVariables.Lights[3].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].position");
	::g_ShaderUniformVariables.Lights[3].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].halfVector");
	::g_ShaderUniformVariables.Lights[3].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].coneDirection");
	::g_ShaderUniformVariables.Lights[3].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[3].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].spotExponent");
	::g_ShaderUniformVariables.Lights[3].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].constantAttenuation");
	::g_ShaderUniformVariables.Lights[3].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].linearAttenuation");
	::g_ShaderUniformVariables.Lights[3].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[3].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[4].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].isEnabled");
	::g_ShaderUniformVariables.Lights[4].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].isLocal");
	::g_ShaderUniformVariables.Lights[4].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].isSpot");
	::g_ShaderUniformVariables.Lights[4].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].ambient");
	::g_ShaderUniformVariables.Lights[4].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].color");
	::g_ShaderUniformVariables.Lights[4].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].position");
	::g_ShaderUniformVariables.Lights[4].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].halfVector");
	::g_ShaderUniformVariables.Lights[4].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].coneDirection");
	::g_ShaderUniformVariables.Lights[4].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[4].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].spotExponent");
	::g_ShaderUniformVariables.Lights[4].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].constantAttenuation");
	::g_ShaderUniformVariables.Lights[4].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].linearAttenuation");
	::g_ShaderUniformVariables.Lights[4].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[4].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[5].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].isEnabled");
	::g_ShaderUniformVariables.Lights[5].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].isLocal");
	::g_ShaderUniformVariables.Lights[5].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].isSpot");
	::g_ShaderUniformVariables.Lights[5].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].ambient");
	::g_ShaderUniformVariables.Lights[5].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].color");
	::g_ShaderUniformVariables.Lights[5].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].position");
	::g_ShaderUniformVariables.Lights[5].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].halfVector");
	::g_ShaderUniformVariables.Lights[5].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].coneDirection");
	::g_ShaderUniformVariables.Lights[5].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[5].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].spotExponent");
	::g_ShaderUniformVariables.Lights[5].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].constantAttenuation");
	::g_ShaderUniformVariables.Lights[5].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].linearAttenuation");
	::g_ShaderUniformVariables.Lights[5].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[5].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[6].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].isEnabled");
	::g_ShaderUniformVariables.Lights[6].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].isLocal");
	::g_ShaderUniformVariables.Lights[6].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].isSpot");
	::g_ShaderUniformVariables.Lights[6].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].ambient");
	::g_ShaderUniformVariables.Lights[6].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].color");
	::g_ShaderUniformVariables.Lights[6].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].position");
	::g_ShaderUniformVariables.Lights[6].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].halfVector");
	::g_ShaderUniformVariables.Lights[6].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].coneDirection");
	::g_ShaderUniformVariables.Lights[6].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[6].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].spotExponent");
	::g_ShaderUniformVariables.Lights[6].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].constantAttenuation");
	::g_ShaderUniformVariables.Lights[6].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].linearAttenuation");
	::g_ShaderUniformVariables.Lights[6].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[6].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[7].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].isEnabled");
	::g_ShaderUniformVariables.Lights[7].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].isLocal");
	::g_ShaderUniformVariables.Lights[7].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].isSpot");
	::g_ShaderUniformVariables.Lights[7].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].ambient");
	::g_ShaderUniformVariables.Lights[7].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].color");
	::g_ShaderUniformVariables.Lights[7].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].position");
	::g_ShaderUniformVariables.Lights[7].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].halfVector");
	::g_ShaderUniformVariables.Lights[7].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].coneDirection");
	::g_ShaderUniformVariables.Lights[7].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[7].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].spotExponent");
	::g_ShaderUniformVariables.Lights[7].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].constantAttenuation");
	::g_ShaderUniformVariables.Lights[7].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].linearAttenuation");
	::g_ShaderUniformVariables.Lights[7].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[7].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[8].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].isEnabled");
	::g_ShaderUniformVariables.Lights[8].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].isLocal");
	::g_ShaderUniformVariables.Lights[8].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].isSpot");
	::g_ShaderUniformVariables.Lights[8].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].ambient");
	::g_ShaderUniformVariables.Lights[8].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].color");
	::g_ShaderUniformVariables.Lights[8].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].position");
	::g_ShaderUniformVariables.Lights[8].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].halfVector");
	::g_ShaderUniformVariables.Lights[8].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].coneDirection");
	::g_ShaderUniformVariables.Lights[8].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[8].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].spotExponent");
	::g_ShaderUniformVariables.Lights[8].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].constantAttenuation");
	::g_ShaderUniformVariables.Lights[8].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].linearAttenuation");
	::g_ShaderUniformVariables.Lights[8].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[8].quadraticAttenuation");

	::g_ShaderUniformVariables.Lights[9].isEnabled_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].isEnabled");
	::g_ShaderUniformVariables.Lights[9].isLocal_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].isLocal");
	::g_ShaderUniformVariables.Lights[9].isSpot_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].isSpot");
	::g_ShaderUniformVariables.Lights[9].ambient_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].ambient");
	::g_ShaderUniformVariables.Lights[9].color_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].color");
	::g_ShaderUniformVariables.Lights[9].position_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].position");
	::g_ShaderUniformVariables.Lights[9].halfVector_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].halfVector");
	::g_ShaderUniformVariables.Lights[9].coneDirection_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].coneDirection");
	::g_ShaderUniformVariables.Lights[9].spotCosCutoff_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].spotCosCutoff");
	::g_ShaderUniformVariables.Lights[9].spotExponent_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].spotExponent");
	::g_ShaderUniformVariables.Lights[9].constantAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].constantAttenuation");
	::g_ShaderUniformVariables.Lights[9].linearAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].linearAttenuation");
	::g_ShaderUniformVariables.Lights[9].quadraticAttenuation_LocID = glGetUniformLocation(g_ShaderProgram_ID, "Lights[9].quadraticAttenuation");

	// ...  and so on...

	return bNoErrors;
}