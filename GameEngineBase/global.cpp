#include "global.h"


int g_screenWidth = 1400;
int g_screenHeight = 900;
int g_windowHandle = 0;
unsigned int g_FrameCount = 0;

CHRTimer g_simTimer;
bool isWireFrame=false;  CShaderUniformVariables g_ShaderUniformVariables;

GLuint g_ShaderProgram_ID = 0;
GLuint g_VertexShader_ID = 0;
GLuint g_FragmentShader_ID = 0;

clock_t g_LastTime = 0 ;

CCamera* g_pCamera1= 0;
CCamera* g_pCamera2= 0;

Delegator boss;
bool boundingBool = false;

bool isFollow = true ; //By Default it will  follow  player

int playerIndex = 0;

Shader* myGlobalShader;


float timeFrames;
std::string timeState = "UP";

GLuint FrameBufferBasic = 0;

GLuint depthTextureID = 0;
GLuint depthTextureCode = 0 ;
GLuint depthTextureNo = 0;

GLuint shadowTextureID = 0;
GLuint shadowTextureCode = 0 ;
GLuint shadowTextureNo = 0;

GLuint colorShTextureID = 0;
GLuint colorShTextureCode = 0;
GLuint colorShTextureNo  = 0;

GLuint colorTextureID = 0;
GLuint colorTextureCode = 0;
GLuint colorTextureNo  = 0;

GLuint depthTextureRID = 0;
GLuint depthTextureRCode = 0 ;
GLuint depthTextureRNo = 0;

GLuint colorTextureRID = 0;
GLuint colorTextureRCode = 0;
GLuint colorTextureRNo  = 0;

GLuint FrameBufferShadow = 0;
GLuint FrameBufferReflection = 0;
float g_FrameBufferHeight = 0.0;
float g_FrameBufferWidth = 0.0;

Hud* hudObject;
GameManager* gameManager;