#include "global.h" 
#include "master.h"
//#include "collisionTest.h"



static const float g_MAXIMUM_TIME_STEP = 0.1f;		// 10th of a second or 100ms 
float valuechange=0.5f;


void idleFunction(void)
{
	// Update the "simulation" at this point.
	// 1. Get elapsed time
	g_simTimer.Stop();
	float deltaTime = ::g_simTimer.GetElapsedSeconds();
	// Is the number TOO big (we're in a break point or something?)
	if ( deltaTime > g_MAXIMUM_TIME_STEP )
	{	// Yup, so clamp it to a new value
		deltaTime = g_MAXIMUM_TIME_STEP;
	}
	g_simTimer.Start();
	
 	//boss.simulation(deltaTime);
	
	
	
	::g_pCamera1->Update( deltaTime );

    unsigned int skyboxId = boss.getSkyBoxId();
	Vector3D camPos(::g_pCamera1->eye.x , ::g_pCamera1->eye.y , ::g_pCamera1->eye.z);
	
	//boss.updateObject("POSITION", camPos, skyboxId);
	unsigned int sphereId = boss.getSphereId();
	//boss.updateObject("POSITION", camPos, sphereId);
	
	

	glm::vec3 vec3obj;
	vec3obj.x = boss.getPlayerPos(0).x;
	vec3obj.y = boss.getPlayerPos(0).y;
	vec3obj.z = boss.getPlayerPos(0).z;




	/*::g_ShaderUniformVariables.Lights[1].position.x = vec3obj.x;
	::g_ShaderUniformVariables.Lights[1].position.y = vec3obj.y;
	::g_ShaderUniformVariables.Lights[1].position.z = vec3obj.z;*/


	glutPostRedisplay();
	return;
}

void timerFunction(int Value)
{
  if (0 != Value) 
  {


	std::stringstream ss;
	ss << WINDOW_TITLE_PREFIX << ": " 
		<< ::g_FrameCount * 4 << " Frames Per Second @ "
		<< ::g_screenWidth << " x"				// << CurrentWidth << " x "
		<< ::g_screenHeight<< " Balls Defused ->"					// << CurrentHeight;
		<< hudObject->score << " / 4 , Time Left ->"
		<< hudObject->timeLeft;
		

    glutSetWindowTitle(ss.str().c_str());
    //glutSetWindowTitle(TempString);
    //free(TempString);
  }

  ::g_FrameCount = 0;	// FrameCount = 0;
  glutTimerFunc(250, timerFunction, 1);

  return;
}