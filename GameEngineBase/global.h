#ifndef _GLOBAL_GH
#define _GLOBAL_GH

#include <string>
#include "CHRTimer.h"
#include "shaderUniformVariables.h"
#include "camera.h" 
#include <time.h>
#include "delegator.h"
#include "hud.h"
#include "gameManager.h"

//used to define global variables 


extern int g_screenWidth ,g_screenHeight, g_windowHandle ; 
extern unsigned int g_FrameCount ;

static const std::string g_WindowTitleDefault = "OpenGL Game";
#define WINDOW_TITLE_PREFIX "Game Window"


//Function called to initialize everything
bool OpenGL_Initialize(int argc, char* argv[], int screenWidth, int screenHeight);

// OpenGL callbacks
void resizeCallback(int Width, int Height);		
void displayCallback(void);						
void timerFunction(int);
void idleFunction(void);
void closeCallback(void);						
void keyboardCallback(unsigned char key, int x, int y);	
void keyboardUpCallback(unsigned char key, int x, int y);	
void specialKeyCallback( int key, int x, int y );
void specialKeyUpCallback( int key, int x, int y );

//Error checking
void ExitOnGLError(const char* error_message);


//Timer 
extern CHRTimer g_simTimer;

//Shader variables
extern CShaderUniformVariables g_ShaderUniformVariables;



//Shader program info
extern Shader* myGlobalShader;


extern float timeFrames;
extern std::string timeState;


extern float g_FrameBufferHeight;
extern float g_FrameBufferWidth;
	

extern 	GLuint FrameBufferBasic;
extern 	GLuint FrameBufferShadow;
extern 	GLuint FrameBufferReflection;


extern GLuint shadowTextureID;
extern GLuint shadowTextureCode ;
extern GLuint shadowTextureNo ;

extern GLuint colorShTextureID;
extern GLuint colorShTextureCode ;
extern GLuint colorShTextureNo ;


extern GLuint depthTextureID;
extern GLuint depthTextureCode ;
extern GLuint depthTextureNo ;

extern GLuint colorTextureID;
extern GLuint colorTextureCode ;
extern GLuint colorTextureNo ;

extern GLuint colorTextureRID;
extern GLuint colorTextureRCode ;
extern GLuint colorTextureRNo ;

extern GLuint depthTextureRID;
extern GLuint depthTextureRCode ;
extern GLuint depthTextureRNo ;

//Time
extern clock_t g_LastTime ;


//Camera object
extern CCamera* g_pCamera1;
extern CCamera* g_pCamera2;

//Delegator
extern Delegator boss;
extern bool boundingBool;
//To toggle camera mode
extern bool isFollow;
extern int playerIndex;
extern Hud* hudObject;
extern GameManager* gameManager;
#endif