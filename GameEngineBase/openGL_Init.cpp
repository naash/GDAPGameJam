#include "master.h"
#include "global.h"


bool InitWindow(int argc, char* argv[], int screenWidth, int screenHeight)
{
	glutInit(&argc, argv);

	::g_screenWidth = screenWidth;
	::g_screenHeight = screenHeight;
  
	//glutInitContextVersion(3, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
	GLUT_ACTION_ON_WINDOW_CLOSE,
	GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
  
	glutInitWindowSize( ::g_screenWidth, ::g_screenHeight );

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	
	::g_windowHandle = glutCreateWindow( ::g_WindowTitleDefault.c_str() );

	if ( ::g_windowHandle < 1 )
	{
		
		std::cout << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}


	// Tells GLUT what functions to call... ("callback" functions)
	glutReshapeFunc(resizeCallback);
	glutDisplayFunc(displayCallback);	
	glutIdleFunc(idleFunction);
	glutTimerFunc(0, timerFunction, 0);
	glutCloseFunc(closeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialKeyCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialUpFunc(specialKeyUpCallback);

	return true;
}

bool OpenGL_Initialize(int argc, char* argv[], int screenWidth, int screenHeight)
{
	GLenum GlewInitResult;

	if (! InitWindow(argc, argv, screenWidth, screenHeight) )
	{
		return false;	// Error
	}	

	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) 
	{
		
		std::cout << "ERROR: " << glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}
  	

	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH); 
	//glGetError();
	glClearColor(0.3f, 0.1f, 0.5f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	ExitOnGLError("ERROR: Could not set OpenGL culling options");

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	return true;
}