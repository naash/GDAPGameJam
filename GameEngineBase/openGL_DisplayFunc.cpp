#include "global.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "vertexType.h"		// For CVertex_fXYZ_fRGB, etc.
#include "gameObject.h"
#include "textureData.h"

std::map<std::string , Shader*> shaderData;


// ***********************************************************************************
// ********************************* TOP SECRET CODE *********************************
void SetLightingUniforms(void);
// ********************************* TOP SECRET CODE *********************************
// ***********************************************************************************
void renderObjects(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild = false);
void renderShadows(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild = false);
void renderReflection(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild = false);
void renderToFrame1(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild = false);
void renderToFrame2(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild = false);
void renderQuad(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld, glm::mat4 matView, bool isChild = false);


void displayCallback(void)
{
	//++FrameCount;
	::g_FrameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(hudObject->gameState)
	{
		hudObject->updateTime();
		boss.simulation(0.1f);
	}
	//DrawCube();
	// *********************************
	//float CubeAngle;				// Not needed, anymore

	clock_t Now = clock();

	if ( ::g_LastTime == 0 )	// if (LastTime == 0)
	{
		::g_LastTime = Now;		// LastTime = Now;
	}


	// *********************************
	glm::mat4 matView(1.0f);

	glm::mat4 matWorld = glm::mat4(1.0f);



	// Get the objects we are to render from the factory



	//	::g_SetShaderUniformVariables();
	shaderData = boss.getShaders();
	boss.callFunc("RENDER");


	renderShadows(boss.getSceneList(), matWorld, matView); //Make Shadow Map
	renderReflection(boss.getSceneList(), matWorld, matView); //Make Shadow Map

	if(::gameManager->isTwoPlayer)
	{
		//Rendering split screen 
		renderToFrame2(boss.getSceneList(), matWorld, matView); //Pass 1
	}
	else
	{
		//Rendering single screen
		renderToFrame1(boss.getSceneList(), matWorld, matView); //Pass 1
	}


	//renderShadowMap(boss.getSceneList(), matWorld, matView); //Pass 1 
	//glutSwapBuffers();
	//glDisable(GL_DEPTH_TEST);
	//glUseProgram(0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	renderQuad(boss.getSceneList(), matWorld, matView); //Pass 2


	boss.callFunc("ENDRENDER");





	// Detatch from the vertex buffer (0 is reserved in OpenGL, so setting to "0" means "set to nothing", sort of)
	glBindVertexArray(0);

	// Detatch from the current shader program
	glUseProgram(0);
	hudObject->renderText();
	glutSwapBuffers();
	return;
}

// ***********************************************************************************
// ********************************* TOP SECRET CODE *********************************
void SetLightingUniforms(void)
{
	for (int index = 0; index < ::g_ShaderUniformVariables.MaxLights; index++ )
	{

		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isEnabled_LocID, ::g_ShaderUniformVariables.Lights[index].isEnabled );
		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isLocal_LocID, ::g_ShaderUniformVariables.Lights[index].isLocal );
		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isSpot_LocID, ::g_ShaderUniformVariables.Lights[index].isSpot );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].ambient_LocID, ::g_ShaderUniformVariables.Lights[index].ambient.r, 
			::g_ShaderUniformVariables.Lights[index].ambient.g,
			::g_ShaderUniformVariables.Lights[index].ambient.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].color_LocID, ::g_ShaderUniformVariables.Lights[index].color.r, 
			::g_ShaderUniformVariables.Lights[index].color.g,
			::g_ShaderUniformVariables.Lights[index].color.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].position_LocID, ::g_ShaderUniformVariables.Lights[index].position.r, 
			::g_ShaderUniformVariables.Lights[index].position.g,
			::g_ShaderUniformVariables.Lights[index].position.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].halfVector_LocID, ::g_ShaderUniformVariables.Lights[index].halfVector.r, 
			::g_ShaderUniformVariables.Lights[index].halfVector.g,
			::g_ShaderUniformVariables.Lights[index].halfVector.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].coneDirection_LocID, ::g_ShaderUniformVariables.Lights[index].coneDirection.r, 
			::g_ShaderUniformVariables.Lights[index].coneDirection.g,
			::g_ShaderUniformVariables.Lights[index].coneDirection.b );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].spotCosCutoff_LocID, ::g_ShaderUniformVariables.Lights[index].spotCosCutoff );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].spotExponent_LocID, ::g_ShaderUniformVariables.Lights[index].spotExponent );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].constantAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].constantAttenuation );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].linearAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].linearAttenuation );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].quadraticAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].quadraticAttenuation );

	}
	return;
}



void renderQuad(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld, glm::mat4 matView, bool isChild)
{
	glActiveTexture(GL_TEXTURE0); // Reseting the active texture

	matView = glm::lookAt( glm::vec3(0.0, 0.0, 6.0 ),			// Camera (aka "Eye")
		glm::vec3(0.0, 0.0,-1.0 ),		// At (aka "target")
		glm::vec3(0.0, 1.0, 0.0 ) );		// Up

	glViewport( 0, 0, ::g_screenWidth, ::g_screenHeight );
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)::g_screenWidth / ::g_screenHeight, 0.1f, 200.0f);
	UniformData data;

	data.mat4Data = proj;


	//matView = glm::lookAt( glm::vec3(g_pCamera1->eye.x, g_pCamera1->eye.y, g_pCamera1->eye.z),			// Camera (aka "Eye")
	//			glm::vec3(0.0, 0.0,-1.0 ),	// At (aka "target")
	//		glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	int index = vec_pRenderedObjects.size() - 1;
	//for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size()); index++)
	//{
	glm::mat4 matWorld1;
	//shaderData[vec_pRenderedObjects[index]->shaderName]->enableShader();
	::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];


	::myGlobalShader->enableShader();

	::myGlobalShader->setUniformVariable("ProjectionMatrix", data, false);
	//::g_SetShaderUniformVariables(shaderData[vec_pRenderedObjects[index]->shaderName]->getProgramID());
	::g_SetShaderUniformVariables(myGlobalShader->getProgramID());

	if (!isChild)
	{
		matWorld1 = glm::mat4(1.0f);


	}else
	{
		matWorld1 = matWorld;

	}



	data.textureNumData = colorTextureNo ;
	data.textureBindData = colorTextureID;
	data.textureCodeData =  colorTextureCode;
	::myGlobalShader->setUniformVariable("texture1", data, true);


	//TextureData* textures = boss.getTexture("dudvWater");
	////Reflected Texture
	//data.textureNumData = textures->getTextureNo();// shadowTextureNo ;
	//data.textureBindData = textures->getTextureID();// shadowTextureID;
	//data.textureCodeData =  textures->getTextureCode(); //shadowTextureCode;
	//::myGlobalShader->setUniformVariable("texture1",data,true);

	/*	data.textureNumData = shadowTextureNo ;
	data.textureBindData = shadowTextureID;
	data.textureCodeData =  shadowTextureCode;*/




	//Goes to the GameObject RenderFunction
	vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 2);


	//}


}

void renderObjects(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld, glm::mat4 matView, bool isChild)
{

	glViewport( 0, 0, ::g_screenWidth, ::g_screenHeight );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size()) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;



		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}


		::myGlobalShader->enableShader();

		if(vec_pRenderedObjects[index]->shaderName == "simple")
		{
			SetLightingUniforms();

			UniformData data;
			data.textureBindData = shadowTextureID;
			data.textureCodeData = shadowTextureCode;
			data.textureNumData = shadowTextureNo;

			::myGlobalShader->setUniformVariable("shadowMap",data, false);


			glm::vec3 eye = ::g_ShaderUniformVariables.Lights[0].position ;
			glm::vec3 target = ::g_ShaderUniformVariables.Lights[0].halfVector;
			glm::vec3 up = glm::vec3(0.0,1.0,0.0);

			glm::mat4 matLightView = glm::lookAt( eye,	glm::vec3(0.0),	 up );		

			data.mat4Data = matLightView;

			::myGlobalShader->setUniformVariable("lightViewMatrix",data, false);

			// matView = matLightView;

		}


		ExitOnGLError("ERROR: Could not use the shader program");


		//Goes to the GameObject RenderFunction
		vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 1);
		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'


}


void renderToFrame1(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld, glm::mat4 matView, bool isChild)
{
	Vector3D playerPos = boss.getPlayerPos(playerIndex);
	Vector3D cameEye = playerPos + g_pCamera1->offset;


	


	


	if(isFollow)
	{
		//g_pCamera1->eye = playerPos + Vector3D(5*cos(boss.getPlayerRotation(0).x), 1, 5*sin(boss.getPlayerRotation(0).x));
		g_pCamera1->eye = playerPos + Vector3D(-5*cos(boss.getPlayerRotation(0).z), 1, 5*sin(boss.getPlayerRotation(0).z));


		//g_pCamera1->eye =  Vector3D(playerPos.x, playerPos.y+1, playerPos.z+ 5);
			matView = glm::lookAt( glm::vec3(g_pCamera1->eye.x, g_pCamera1->eye.y, g_pCamera1->eye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}
	else
	{

		matView = glm::lookAt( glm::vec3(g_pCamera1->eye.x, g_pCamera1->eye.y, g_pCamera1->eye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}

	glm::vec3 lightInvDir = glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z) ;//glm::vec3(0.5f,2,2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix  = glm::ortho<float>(-5,5,-5,5,-5,20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));

	//matView = glm::lookAt( lightInvDir,			// Camera (aka "Eye")
	//glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
	//glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up	



	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferBasic );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, ::g_FrameBufferWidth, ::g_FrameBufferHeight);

	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size() - 1) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;

		//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
		std::map<std::string , UniformData> uniformData;


		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)::g_screenWidth / ::g_screenHeight, 0.1f, 500.0f);
		UniformData data;


		::myGlobalShader->enableShader();

		data.mat4Data = proj;
		::myGlobalShader->setUniformVariable("ProjectionMatrix", data, false);


		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}




		if(vec_pRenderedObjects[index]->shaderName == "simple")
		{
			SetLightingUniforms();





			data.textureNumData = shadowTextureNo ;
			data.textureBindData = shadowTextureID;
			data.textureCodeData =  shadowTextureCode;


			myGlobalShader->setUniformVariable("shadowMap", data, true);




		}
		if(vec_pRenderedObjects[index]->shaderName == "water")
		{
			data.floatData = 1.0f;

			data.floatData = timeFrames;
			uniformData["waveFactor"] = data;


			TextureData* textures = boss.getTexture("waterText");
			//Reflected Texture
			data.textureNumData =colorTextureRNo;// shadowTextureNo ;
			data.textureBindData = colorTextureRID;// shadowTextureID;
			data.textureCodeData =  colorTextureRCode; //shadowTextureCode;
			::myGlobalShader->setUniformVariable("water_reflection",data,true);



			//Refracted Texture (same currently)
			data.textureNumData =colorTextureRNo;// shadowTextureNo ;
			data.textureBindData = colorTextureRID;// shadowTextureID;
			data.textureCodeData =  colorTextureRCode; //shadowTextureCode;
			::myGlobalShader->setUniformVariable("water_refraction",data,true);

			//Depth Map
			data.textureNumData = depthTextureRNo ;
			data.textureBindData = depthTextureRID;
			data.textureCodeData =  depthTextureRCode;
			//uniformData["water_depthmap"] = data;
			::myGlobalShader->setUniformVariable("water_depthmap",data,true);


			//Normal Map
			textures = boss.getTexture("normalWater");
			data.textureNumData = textures->getTextureNo();// shadowTextureNo ;
			data.textureBindData = textures->getTextureID();// shadowTextureID;
			data.textureCodeData =  textures->getTextureCode(); //shadowTextureCode;
			uniformData["water_normalmap"] = data;

			//DUDV Map
			textures = boss.getTexture("dudvWater");
			data.textureNumData = textures->getTextureNo();// shadowTextureNo ;
			data.textureBindData = textures->getTextureID();// shadowTextureID;
			data.textureCodeData =  textures->getTextureCode(); //shadowTextureCode;
			uniformData["water_dudvmap"] = data;



			//viewpos
			data.float4Data[0] = ::g_pCamera1->eye.x ;
			data.float4Data[1] = ::g_pCamera1->eye.y ;
			data.float4Data[2] = ::g_pCamera1->eye.z ;
			data.float4Data[3] = 1.0 ;
			uniformData["viewpos"] = data;


			//lightpos
			data.float4Data[0] = ::g_ShaderUniformVariables.Lights[0].position.x ;
			data.float4Data[1] = ::g_ShaderUniformVariables.Lights[0].position.y ;
			data.float4Data[2] = ::g_ShaderUniformVariables.Lights[0].position.z ;
			data.float4Data[3] = 1.0 ;
			uniformData["lightpos"] = data;

			//waterColor
			data.float4Data[0] = 0.1 ;
			data.float4Data[1] = 0.1 ;
			data.float4Data[2] = 0.8 ;
			data.float4Data[3] = 1.0 ;
			uniformData["waterColor"] = data;

			//waterDepth
			data.float4Data[0] = 0.0 ;
			data.float4Data[1] = -5.0 ;
			data.float4Data[2] = 0.0 ;
			data.float4Data[3] = 1.0 ;
			uniformData["waterDepth"] = data;


			//time
			data.floatData = timeFrames;
			uniformData["time"] = data;


			//time2
			data.floatData = -timeFrames;
			uniformData["time2"] = data;



			::myGlobalShader->setUniformVariablesInBulk(uniformData);
		}





		ExitOnGLError("ERROR: Could not use the shader program");


		//Goes to the GameObject RenderFunction
		if(vec_pRenderedObjects[index]->shaderName == "water")
		{
			vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 2 ,depthProjectionMatrix, depthViewMatrix);
		}
		else
		{
			vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 1 ,depthProjectionMatrix, depthViewMatrix);
		}

		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(0);



	if(timeFrames > 0.1)
	{
		timeState = "DOWN";
	}else if(timeFrames < -0.1)
	{
		timeState = "UP";
	}


	if(timeState == "UP")
		timeFrames +=0.0001f;
	else
	{
		timeFrames -=0.0001f;

	}
}


void renderToFrame2(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild)
{
	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferBasic );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);


	//.........................................................................Left Side player 2 .........................................................................//
	glViewport(0, 0, ::g_FrameBufferWidth/2, ::g_FrameBufferHeight);

	Vector3D playerPos = boss.getPlayerPos(playerIndex +1);
	Vector3D cameEye = playerPos + g_pCamera2->offset;

	if(isFollow)
	{
		//g_pCamera1->eye =  Vector3D(playerPos.x, playerPos.y+1, playerPos.z+ 5);
		matView = glm::lookAt( glm::vec3(cameEye.x, cameEye.y, cameEye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera2->up.x, g_pCamera2->up.y, g_pCamera2->up.z) );		// Up
	}
	else
	{

		matView = glm::lookAt( glm::vec3(g_pCamera2->eye.x, g_pCamera2->eye.y, g_pCamera2->eye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera2->up.x, g_pCamera2->up.y, g_pCamera2->up.z) );		// Up
	}

	glm::vec3 lightInvDir = glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z) ;//glm::vec3(0.5f,2,2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix  = glm::ortho<float>(-5,5,-5,5,-5,20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));





	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size() - 1) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
		std::map<std::string , UniformData> uniformData;

		::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;

		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)(::g_screenWidth/2) / ::g_screenHeight, 0.1f, 500.0f);
		UniformData data;


		::myGlobalShader->enableShader();

		data.mat4Data = proj;
		::myGlobalShader->setUniformVariable("ProjectionMatrix", data, false);


		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}




		if(vec_pRenderedObjects[index]->shaderName == "simple")
		{
			SetLightingUniforms();




			data.textureNumData = shadowTextureNo ;
			data.textureBindData = shadowTextureID;
			data.textureCodeData =  shadowTextureCode;


			myGlobalShader->setUniformVariable("shadowMap", data, true);




		}


		ExitOnGLError("ERROR: Could not use the shader program");


		//Goes to the GameObject RenderFunction
		vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 1 ,depthProjectionMatrix, depthViewMatrix);
		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	//.........................................................................Right Side player 1 .........................................................................//

	matView =glm::mat4(1.0f);

	//glViewport(::g_FrameBufferWidth/2 , 0 ,::g_FrameBufferWidth , ::g_FrameBufferHeight);
	glViewport(::g_FrameBufferWidth/2 , 0 ,::g_FrameBufferWidth/2 , ::g_FrameBufferHeight);
	playerPos = boss.getPlayerPos(playerIndex);
	cameEye = playerPos + g_pCamera1->offset;

	if(isFollow)
	{
		//g_pCamera1->eye =  Vector3D(playerPos.x, playerPos.y+1, playerPos.z+ 5);
		matView = glm::lookAt( glm::vec3(cameEye.x, cameEye.y, cameEye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}
	else
	{

		matView = glm::lookAt( glm::vec3(g_pCamera1->eye.x, g_pCamera1->eye.y, g_pCamera1->eye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}

	//glm::vec3 lightInvDir = glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z) ;//glm::vec3(0.5f,2,2);

	//		// Compute the MVP matrix from the light's point of view
	//		glm::mat4 depthProjectionMatrix  = glm::ortho<float>(-10,10,-10,10,-10,20);
	//		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));

	//		glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix ;



	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size() - 1) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;

		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)(::g_screenWidth/2) / ::g_screenHeight, 0.1f, 500.0f);
		UniformData data;


		//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
		std::map<std::string , UniformData> uniformData;

		::myGlobalShader->enableShader();

		data.mat4Data = proj;
		::myGlobalShader->setUniformVariable("ProjectionMatrix", data, false);


		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}



		if(vec_pRenderedObjects[index]->shaderName == "simple")
		{
			SetLightingUniforms();






			data.textureNumData = shadowTextureNo ;
			data.textureBindData = shadowTextureID;
			data.textureCodeData =  shadowTextureCode;


			myGlobalShader->setUniformVariable("shadowMap", data, true);




		}


		ExitOnGLError("ERROR: Could not use the shader program");


		//Goes to the GameObject RenderFunction
		vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 1 ,depthProjectionMatrix, depthViewMatrix);
		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	//.........................................................................Right Side player 1 .........................................................................//

	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(0);
}


void renderShadows(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld,glm::mat4 matView,  bool isChild)
{

	matView = glm::lookAt( glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z),			// Camera (aka "Eye")
		glm::vec3(0.0, 0.0, -1.0),		// At (aka "target")
		glm::vec3(0.0, 1.0, 0.0) );		// Up


	glActiveTexture(GL_TEXTURE0); // Reseting the active texture
	glDepthRange(0.0f, 1.0f);

	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferShadow );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, ::g_FrameBufferWidth, ::g_FrameBufferHeight);


	::myGlobalShader = shaderData["shadow"];


	//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
	std::map<std::string , UniformData> uniformData;
	UniformData data;



	glm::vec3 lightInvDir =glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z) ;//glm::vec3(0.5f,2,2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix =glm::ortho<float>(-5,5,-5,5,-5,20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));


	for (int index = 1; index != static_cast<int>(vec_pRenderedObjects.size() - 1) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		//::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;



		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}


		::myGlobalShader->enableShader();


		ExitOnGLError("ERROR: Could not use the shader program");


		//Goes to the GameObject RenderFunction
		vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 3, depthProjectionMatrix , depthViewMatrix);
		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	glBindFramebuffer( GL_FRAMEBUFFER, 0);
}

void renderReflection(std::vector< GameObject* > vec_pRenderedObjects, glm::mat4 matWorld, glm::mat4 matView, bool isChild)
{
	Vector3D playerPos = boss.getPlayerPos(playerIndex);
	Vector3D cameEye = playerPos + g_pCamera1->offset;

	if(isFollow)
	{
		//g_pCamera1->eye =  Vector3D(playerPos.x, playerPos.y+1, playerPos.z+ 5);
		matView = glm::lookAt( glm::vec3(cameEye.x, cameEye.y, cameEye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}
	else
	{

		matView = glm::lookAt( glm::vec3(g_pCamera1->eye.x, g_pCamera1->eye.y, g_pCamera1->eye.z),			// Camera (aka "Eye")
			glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
			glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up
	}

	glm::vec3 lightInvDir = glm::vec3(::g_ShaderUniformVariables.Lights[0].position.x, ::g_ShaderUniformVariables.Lights[0].position.y, ::g_ShaderUniformVariables.Lights[0].position.z) ;//glm::vec3(0.5f,2,2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix  = glm::ortho<float>(-5,5,-5,5,-5,20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));

	//matView = glm::lookAt( lightInvDir,			// Camera (aka "Eye")
	//glm::vec3(playerPos.x,playerPos.y,playerPos.z),		// At (aka "target")
	//glm::vec3(g_pCamera1->up.x, g_pCamera1->up.y, g_pCamera1->up.z) );		// Up	



	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferReflection );



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, ::g_FrameBufferWidth, ::g_FrameBufferHeight);


	double plane[4] = {0.0, 0.5, 0.0, 0.0}; //water at y=0
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, plane);

	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size() - 1) ; index++)
	{

		if(vec_pRenderedObjects[index]->getName().find("checkpoint") != std::string::npos)
			continue;


		::myGlobalShader = shaderData[vec_pRenderedObjects[index]->shaderName];

		glm::mat4 matWorld1;

		//Pack data to be sent to shader   /////////////////////////////////////////////////////////////
		std::map<std::string , UniformData> uniformData;


		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)::g_screenWidth / ::g_screenHeight, 0.1f, 500.0f);
		UniformData data;


		::myGlobalShader->enableShader();

		data.mat4Data = proj;
		::myGlobalShader->setUniformVariable("ProjectionMatrix", data, false);


		if (!isChild)
		{
			matWorld1 = glm::mat4(1.0f);
		}
		else
		{
			matWorld1 = matWorld;
		}








		ExitOnGLError("ERROR: Could not use the shader program");



		vec_pRenderedObjects[index]->render(matWorld1,matView, ::myGlobalShader, 4 ,depthProjectionMatrix, depthViewMatrix);


		//glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld1));

		ExitOnGLError("ERROR: Could not set the shader uniforms");

		if (boundingBool == true)
		{
			//If GameObjects has child objects
			if (vec_pRenderedObjects[index]->hasChildObjects())
			{
				renderObjects(vec_pRenderedObjects[index]->getChildObjects(), matWorld1,matView, true);
			}

		}
	}


	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'
	glDisable(GL_CLIP_PLANE0);
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glUseProgram(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(timeFrames > 0.1)
	{
		timeState = "DOWN";
	}else if(timeFrames < -0.1)
	{
		timeState = "UP";
	}


	if(timeState == "UP")
		timeFrames +=0.0001f;
	else
	{
		timeFrames -=0.0001f;

	}
}