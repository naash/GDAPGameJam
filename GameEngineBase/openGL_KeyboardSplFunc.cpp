#include "global.h"
#include "master.h"

float textMixVal = 0.0f;

void keyboardCallback(unsigned char key, int x, int y)
{
	//Get id of player
	unsigned int playerId = boss.getPlayerId(playerIndex);
	unsigned int skyboxId = boss.getSkyBoxId();
	Vector3D oldPos;
	switch( key )
	{
	case ' ':		// Space
		{
			//Stops player
			boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),playerId);
			boss.updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.0f),playerId);

		}
		break;

	case 'o': case 'O':
		// Print Player Position
		std::cout<<"Player is at x : "<<boss.getPlayerPos(playerIndex).x<<" y : "<<boss.getPlayerPos(playerIndex).y<<" z : "<<boss.getPlayerPos(playerIndex).z<<std::endl;

		break;	
		//Camera Controls.............. start
	case 'i': case 'I':
		if(!isFollow)
		{
			::g_pCamera1->eye.z -= 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.z -= 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		::g_ShaderUniformVariables.Lights[0].position.z += 0.1f;
		break;
	case 'k': case 'K':
		if(!isFollow)
		{
			::g_pCamera1->eye.z += 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.z += 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		::g_ShaderUniformVariables.Lights[0].position.z -= 0.1f;
		break;
	case 'j': case 'J':
		if(!isFollow)
		{
			::g_pCamera1->eye.x -= 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.x -= 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		::g_ShaderUniformVariables.Lights[0].position.x -= 0.1f;
		break;
	case 'l': case 'L':
		if(!isFollow)
		{
			::g_pCamera1->eye.x += 0.1f;	// Back (-ve z)
			oldPos = boss.getSkyboxPos();
			oldPos.x += 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}

		::g_ShaderUniformVariables.Lights[0].position.x += 0.1f;
		break;
		//Camera Controls.............. end
	case 't': case 'T':
		/*textMixVal += 0.01f;
		if (textMixVal > 1.0f)
		{
		textMixVal = 1.0f;
		}
		boss.setTextureMixVal("Sub", textMixVal);*/
		::g_ShaderUniformVariables.Lights[0].position.y += 0.1f;

		::g_ShaderUniformVariables.Lights[12].constantAttenuation += 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].linearAttenuation += 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].quadraticAttenuation += 0.01f ; 
		break;

	case 'y': case 'Y':
		/*textMixVal -= 0.01f;
		if (textMixVal < 0.0f)
		{
		textMixVal = 0.0f;
		}
		boss.setTextureMixVal("Sub", textMixVal);*/
		::g_ShaderUniformVariables.Lights[0].position.y -= 0.1f;
		::g_ShaderUniformVariables.Lights[12].constantAttenuation -= 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].linearAttenuation -= 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].quadraticAttenuation -= 0.01f ; 
		break;

	case 'w': case 'W':
		if(::gameManager->isTwoPlayer)
			boss.userInput(ACCELERATE, 1);
		break;
	case 's': case 'S':
		if(::gameManager->isTwoPlayer)
			boss.userInput(BRAKES, 1);
		break;

	case 'a': case 'A':
		if(::gameManager->isTwoPlayer)
			boss.userInput(LEFT, 1);
		break;
	case 'd': case 'D':
		if(::gameManager->isTwoPlayer)
			boss.userInput(RIGHT, 1);
		break;
	case 'f' : case 'F' :
		isFollow = !isFollow;
		break;
	};

	return;
}


void keyboardUpCallback(unsigned char key, int x, int y)
{
	//Get id of player
	unsigned int playerId = boss.getPlayerId(playerIndex);
	unsigned int skyboxId = boss.getSkyBoxId();
	Vector3D oldPos;
	switch( key )
	{
	case ' ':		// Space
		{
			//Stops player
			boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),playerId);
			boss.updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.0f),playerId);

		}
		break;

	case 'o': case 'O':
		// Print Player Position
		std::cout<<"Player is at x : "<<boss.getPlayerPos(playerIndex).x<<" y : "<<boss.getPlayerPos(playerIndex).y<<" z : "<<boss.getPlayerPos(playerIndex).z<<std::endl;

		break;	
		//Camera Controls.............. start
	case 'i': case 'I':
		if(!isFollow)
		{
			::g_pCamera1->eye.z -= 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.z -= 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		break;
	case 'k': case 'K':
		if(!isFollow)
		{
			::g_pCamera1->eye.z += 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.z += 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		break;
	case 'j': case 'J':
		if(!isFollow)
		{
			::g_pCamera1->eye.x -= 0.1f;
			oldPos = boss.getSkyboxPos();
			oldPos.x -= 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		break;
	case 'l': case 'L':
		if(!isFollow)
		{
			::g_pCamera1->eye.x += 0.1f;	// Back (-ve z)
			oldPos = boss.getSkyboxPos();
			oldPos.x += 0.1f;
			boss.updateObject("POSITION", oldPos, skyboxId);
		}
		break;
		//Camera Controls.............. end
	case 't': case 'T':
		/*textMixVal += 0.01f;
		if (textMixVal > 1.0f)
		{
		textMixVal = 1.0f;
		}
		boss.setTextureMixVal("Sub", textMixVal);*/
		::g_ShaderUniformVariables.Lights[0].position.y += 0.1f;

		::g_ShaderUniformVariables.Lights[12].constantAttenuation += 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].linearAttenuation += 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].quadraticAttenuation += 0.01f ; 
		break;

	case 'y': case 'Y':
		/*textMixVal -= 0.01f;
		if (textMixVal < 0.0f)
		{
		textMixVal = 0.0f;
		}
		boss.setTextureMixVal("Sub", textMixVal);*/
		::g_ShaderUniformVariables.Lights[0].position.y -= 0.1f;
		::g_ShaderUniformVariables.Lights[12].constantAttenuation -= 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].linearAttenuation -= 0.01f ; 
		::g_ShaderUniformVariables.Lights[12].quadraticAttenuation -= 0.01f ; 
		break;

	case 'w': case 'W':
		if(::gameManager->isTwoPlayer)
			//boss.userInput(ACCELERATE, 1);
		break;
	case 's': case 'S':
		if(::gameManager->isTwoPlayer)
		//	boss.userInput(BRAKES, 1);
		break;

	case 'a': case 'A':
		if(::gameManager->isTwoPlayer)
			boss.userInput(DIRECTIONRESET, 1);
		break;
	case 'd': case 'D':
		if(::gameManager->isTwoPlayer)
			boss.userInput(DIRECTIONRESET, 1);
		break;
	case 'f' : case 'F' :
		//isFollow = !isFollow;
		break;
	};

	return;
}


void specialKeyCallback( int key, int x, int y )
{

	//std::vector <unsigned int> playerlist = boss.getPlayerId();

	switch ( key )
	{
	case GLUT_KEY_UP:
		{
			//boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, -0.5f),boss.getPlayerId(playerIndex));
			boss.userInput(ACCELERATE, 0);
			//boss.updateObject("VELOCITY", Vector3D(0.0f, 0.0f, -1.0f),boss.getPlayerId(playerIndex));	
		}
		break;
	case GLUT_KEY_DOWN:
		{

			//boss.updateObject("ACCELERATION", Vector3D(0.0f,0.0f,0.5f), boss.getPlayerId(playerIndex));
			boss.userInput(BRAKES, 0);
			//	boss.updateObject("VELOCITY", Vector3D(0.0f,0.0f,1.0f), boss.getPlayerId(playerIndex));

		}
		break;
	case GLUT_KEY_LEFT:
		{   
			//boss.updateObject("ACCELERATION", Vector3D(-0.5f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));
			boss.userInput(LEFT, 0);
			::g_pCamera1->offset.z += 0.05f;
			//::g_pCamera1->offset.x += 0.01f;
			//boss.updateObject("VELOCITY", Vector3D(-1.0f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));
		}
		break;
	case GLUT_KEY_RIGHT:
		{       
			//boss.updateObject("ACCELERATION", Vector3D(0.5f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));
			boss.userInput(RIGHT, 0);
			::g_pCamera1->offset.z -= 0.05f;
			//::g_pCamera1->offset.x += 0.01f;
			//boss.updateObject("VELOCITY", Vector3D(1.0f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));

		}
		break;
	case GLUT_KEY_ALT_R:
		{       
			//Handbrake
			//boss.updateObject("ACCELERATION", Vector3D(0.5f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));

			boss.userInput(HANDBRAKES, 0);
			//boss.updateObject("VELOCITY", Vector3D(1.0f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));

		}
		break;
	case GLUT_KEY_ALT_L:
		{       
			//Handbrake
			//boss.updateObject("ACCELERATION", Vector3D(0.5f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));
			if(::gameManager->isTwoPlayer)
				boss.userInput(HANDBRAKES, 1);
			//boss.updateObject("VELOCITY", Vector3D(1.0f, 0.0f, 0.0f), boss.getPlayerId(playerIndex));

		}
		break;
	case GLUT_KEY_CTRL_L:
		{       
			//down
			boss.updateObject("ACCELERATION", Vector3D(0.0f, -0.5f, 0.0f), boss.getPlayerId(playerIndex));
			//	boss.updateObject("VELOCITY", Vector3D(0.0f, -0.5f, 0.0f), boss.getPlayerId(playerIndex));
		}
		break;
	case GLUT_KEY_SHIFT_L:
		{       
			//Up
			boss.updateObject("ACCELERATION", Vector3D(0.0f, +0.5f, 0.0f), boss.getPlayerId(playerIndex));
			//	boss.updateObject("VELOCITY", Vector3D(0.0f, +0.5f, 0.0f), boss.getPlayerId(playerIndex));
		}
		break;
	};




	return;
}


void specialKeyUpCallback( int key, int x, int y )
{

	////std::vector <unsigned int> playerlist = boss.getPlayerId();
	//unsigned int index = boss.getPlayerId();
	//
	//  
	switch ( key )
	{
	case GLUT_KEY_UP:
		{

			//boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),index);	//CMessage theMessage;
		}
		break;
	case GLUT_KEY_DOWN:
		{					 
			//boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),index);//CMessage theMessage;
		}
		break;

	case GLUT_KEY_CTRL_L:
		{       
			//down
			// boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),index);	//CMessage theMessage;
		}
		break;
	case GLUT_KEY_SHIFT_L:
		{       
			//Up
			// boss.updateObject("ACCELERATION", Vector3D(0.0f, 0.0f, 0.0f),index);	//CMessage theMessage;
		}
		break;
	case GLUT_KEY_LEFT:
		{   boss.userInput(DIRECTIONRESET, 0);

		}
		break;
	case GLUT_KEY_RIGHT:
		{       
			boss.userInput(DIRECTIONRESET, 0);

		}
		break;
	};

	//	
	//
	return;
}

