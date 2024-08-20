#ifndef _ShaderUniformVariables_HG_
#define _ShaderUniformVariables_HG_

#include <GL\glew.h>			// Because it complains when we don't include it
#include <GL\freeglut.h>		// Because of the GLuint

#define GLM_FORCE_CXX98    
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> // glm::mat4


// From Fragment shader:
//struct LightProperties
//{
//	bool isEnabled;
//	bool isLocal;
//	bool isSpot;
//	vec3 ambient;
//	vec3 color;
//	vec3 position;
//	vec3 halfVector;
//	vec3 coneDirection;
//	float spotCosCutoff;
//	float spotExponent;
//	float constantAttenuation;
//	float linearAttenuation;
//	float quadraticAttenuation;
//};

struct CLightProperties			//struct LightProperties
{
public:
	CLightProperties(): 
		isEnabled(GL_FALSE), isLocal(GL_FALSE), isSpot(GL_FALSE),
		spotCosCutoff(0.0f), spotExponent(0.0f), 
		constantAttenuation(0.0f), linearAttenuation(0.0f), quadraticAttenuation(0.0f) {};
	GLboolean isEnabled;			GLuint isEnabled_LocID;		//	bool isEnabled;
	GLboolean isLocal;				GLuint isLocal_LocID;		//	bool isLocal;
	GLboolean isSpot;				GLuint isSpot_LocID;		//	bool isSpot;
	glm::vec3 ambient;				GLuint ambient_LocID;		//	vec3 ambient;
	glm::vec3 color;				GLuint color_LocID;			//	vec3 color;
	glm::vec3 position;				GLuint position_LocID;		//	vec3 position;
	glm::vec3 halfVector;			GLuint halfVector_LocID;		//	vec3 halfVector;
	glm::vec3 coneDirection;		GLuint coneDirection_LocID;		//	vec3 coneDirection;
	GLfloat spotCosCutoff;			GLuint spotCosCutoff_LocID;		//	float spotCosCutoff;
	GLfloat spotExponent;			GLuint spotExponent_LocID;		//	float spotExponent;
	GLfloat constantAttenuation;	GLuint constantAttenuation_LocID;	//	float constantAttenuation;
	GLfloat linearAttenuation;		GLuint linearAttenuation_LocID;		//	float linearAttenuation;
	GLfloat quadraticAttenuation;	GLuint quadraticAttenuation_LocID;	//	float quadraticAttenuation;
};

const int MaxLights = 10;

struct CShaderUniformVariables
{
	// From Vertex shader:
	glm::mat4 matProjection;				// uniform mat4 ProjectionMatrix;
	GLuint matProjection_LocationID;		// GLuint g_ProjectionMatrixUniformLocation;			

	glm::mat4 matView;						// uniform mat4 ViewMatrix;
	GLuint matView_LocationID;				// GLuint g_ViewMatrixUniformLocation;		

	glm::mat4 matWorld;						// uniform mat4 ModelMatrix;  
	GLuint matWorld_LocationID;				// GLuint g_ModelMatrixUniformLocation;		

	// From Fragment shader:
	GLfloat Shininess;						// uniform float Shininess;
	GLuint Shininess_LocationID;

	GLfloat Strength;						// uniform float Strength;
	GLuint Strength_LocationID;

	glm::vec3 EyeDirection;					// uniform vec3 EyeDirection
	GLuint EyeDirection_LocationID;

	static const int MaxLights = 10;
	CLightProperties Lights[MaxLights];		// uniform LightProperties Lights[MaxLights];
};


bool g_SetShaderUniformVariables(void);		

//
//// the set of lights to apply, per invocation of this shader
//const int MaxLights = 10;
//uniform LightProperties Lights[MaxLights];
//
//uniform float Shininess;
//uniform float Strength;
//uniform vec3 EyeDirection;


// From Vertex shader:
//
		
//extern GLuint g_ObjectColourUniformLocation;				
//
//extern GLuint g_slot_LightPosition;	//uniform vec4 LightPosition;	
//extern GLuint g_slot_LightColour;	//uniform vec4 LightColour;		
//extern GLuint g_slot_attenuation;	//uniform float attenuation;	

#endif
