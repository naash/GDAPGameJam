#include "global.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "VertexTypes.h"		// For CVertex_fXYZ_fRGB, etc.

// ***********************************************************************************
// ********************************* TOP SECRET CODE *********************************
void SetLightingUniforms(void);
//void renderText();
// ********************************* TOP SECRET CODE *********************************
// ***********************************************************************************



//std::string temp = "Hello Configuration";



void glutDisplay_callback(void)
{

	//++FrameCount;
	::g_FrameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//DrawCube();
	// *********************************
	//float CubeAngle;				// Not needed, anymore

	clock_t Now = clock();

	if (::g_LastTime == 0)	// if (LastTime == 0)
	{
		::g_LastTime = Now;		// LastTime = Now;
	}

	// We aren't using this cube rotation stuff (it was for the pretty coloured cube we had at the start)
	//CubeRotation += 45.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	//CubeAngle = DegreesToRadians(CubeRotation);
	//LastTime = Now;

	// *********************************
	glm::mat4 matView(1.0f);
	//matView = glm::lookAt( glm::vec3(0.0f, 2.0f, 4.0f),			// Camera (aka "Eye")
	//						glm::vec3(0.0f, 0.0f, 0.0f),		// At (aka "target")
	//						glm::vec3(0.0f, 1.0f, 0.0f) );		// Up
	matView = glm::lookAt(glm::vec3(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z),			// Camera (aka "Eye")
		glm::vec3(g_pCamera->target.x, g_pCamera->target.y, g_pCamera->target.z),		// At (aka "target")
		glm::vec3(g_pCamera->up.x, g_pCamera->up.y, g_pCamera->up.z));		// Up


	// Get the objects we are to render from the factory
	std::vector< CGameObject* > vec_pRenderedObjects;
	g_pFactoryMediator->getRenderedObjects(vec_pRenderedObjects);

	// For each object in the vector, we'll draw it...
	//for ( int index = 0; index != ::g_ourObjects.size(); index++ )
	//{
	for (int index = 0; index != static_cast<int>(vec_pRenderedObjects.size()); index++)
	{


		//ModelMatrix = IDENTITY_MATRIX;		/// aka "World" 
		glm::mat4 matWorld = glm::mat4(1.0f);		// aka "World" matrix


		// Set up separate matrices for each type of tranformation
		// Then combine them (by multiplying) into the world matrix.
		// The order you do this impact what you see. 
		// (The last thing you do is the FIRST thing that's applied)
		// (TIP: Put scaling last)
		// (TIP: pre-Rotation, Translation, post-Rotation )


		// Might think about having a "pre" and "post" rotation, one being "orbiting" and one being "spinning" (like a the Earth spinning on its axis)
		//matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->PRErotation.x, glm::vec3(1.0f, 0.0f, 0.0f) );
		//matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->PRErotation.y, glm::vec3(0.0f, 1.0f, 0.0f) );
		//matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->PRErotation.z, glm::vec3(0.0f, 0.0f, 1.0f) );

		matWorld = glm::translate(matWorld, glm::vec3(vec_pRenderedObjects[index]->position.x,
			vec_pRenderedObjects[index]->position.y,
			vec_pRenderedObjects[index]->position.z));

		matWorld = glm::rotate(matWorld, vec_pRenderedObjects[index]->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		matWorld = glm::rotate(matWorld, vec_pRenderedObjects[index]->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		matWorld = glm::rotate(matWorld, vec_pRenderedObjects[index]->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));


		matWorld = glm::scale(matWorld, glm::vec3(vec_pRenderedObjects[index]->scale,
			vec_pRenderedObjects[index]->scale,
			vec_pRenderedObjects[index]->scale));


		//matWorld = glm::translate( matWorld, 
		//	                       glm::vec3( vec_pRenderedObjects[index]->position.x, 
		//						              vec_pRenderedObjects[index]->position.y, 
		//									  vec_pRenderedObjects[index]->position.z) );

		//
		//float scaleTemp = vec_pRenderedObjects[index]->scale;
		//matWorld = glm::scale( matWorld, glm::vec3(scaleTemp) );

		// *** START of DRAW THE OBJECT FROM THE BUFFER ****
		// Add this line
		//glPolygonMode( GL_FRONT,  GL_LINE );
		//glPolygonMode( GL_FRONT_AND_BACK ,  GL_LINE );
		if (wireval)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//glUseProgram(g_ShaderIds[0]);
		glUseProgram(g_ShaderProgram_ID);

		// ***********************************************************************************
		// ********************************* TOP SECRET CODE *********************************
		// NOTE: If we haven't re-linked or switched the shader, the uniform variables -should- be still valid
		::g_SetShaderUniformVariables();

		// Also set the shininess, Strength, EyeDirection (i.e. camera)

		// Set the "EyeDirection" (aka the camera)
		::glUniform3f(::g_ShaderUniformVariables.EyeDirection_LocationID,
			::g_pCamera->eye.x, ::g_pCamera->eye.y, ::g_pCamera->eye.z);

		// Shininess and Strength...
		glUniform1f(::g_ShaderUniformVariables.Shininess_LocationID,
			vec_pRenderedObjects[index]->specularShininess);

		glUniform1f(::g_ShaderUniformVariables.Strength_LocationID,
			vec_pRenderedObjects[index]->specularStrength);

		SetLightingUniforms();
		// ********************************* TOP SECRET CODE *********************************


		// ***********************************************************************************


		ExitOnGLError("ERROR: Could not use the shader program");

		//glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);
		//glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, ViewMatrix.m);
		//glUniformMatrix4fv( g_ModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(matWorld) );
		glUniformMatrix4fv(::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld));
		//glUniformMatrix4fv( g_ViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(matView) );
		glUniformMatrix4fv(::g_ShaderUniformVariables.matView_LocationID, 1, GL_FALSE, glm::value_ptr(matView));

		// Add: setting our colour value we just added
		//glm::vec4 colour;
		//colour.a = 1.0f;	colour.g = 0.5f;	colour.b = 0.3f;	
		//glUniform4f( ObjectColourUniformLocation, colour.r, colour.g, colour.b, 1.0f );

		// Take the colour from the object
		//glUniform4f(g_ObjectColourUniformLocation, vec_pRenderedObjects[index]->colour.x, vec_pRenderedObjects[index]->colour.y, vec_pRenderedObjects[index]->colour.z, 1.0f);	// Colour has 4 components (vec4)




		ExitOnGLError("ERROR: Could not set the shader uniforms");

		//glBindVertexArray(BufferIds[0]);	

		// Based on the object "ply file" name, point to the appropriate buffer

		int numberOfIndicesToRender = 0;
		//if ( vec_pRenderedObjects[index]->plyFileName == "bun_zipper_res3.ply" )
		//{
		//	glBindVertexArray( g_VertexPositionBufferID[1] );				// "Connects" to a vertex buffer
		//	glBindBuffer( GL_ARRAY_BUFFER, g_VertexColourBufferID[1] );		// Also buffer (with colours)
		//	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID[1] );	// And Index buffer	
		//	numberOfIndicesToRender = g_numberOfTriangles[1] * 3; 
		//}
		//else if ( vec_pRenderedObjects[index]->plyFileName == "Utah_Teapot.ply" )
		//{
		//	glBindVertexArray( g_VertexPositionBufferID[0] );				// "Connects" to a vertex buffer
		//	glBindBuffer( GL_ARRAY_BUFFER, g_VertexColourBufferID[0] );		// Also buffer (with colours)
		//	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID[0] );	// And Index buffer	
		//	numberOfIndicesToRender = g_numberOfTriangles[0] * 3; 
		//}
		CPlyInfo tempPlyInfo;
		std::string plyFileNameDEBUG = vec_pRenderedObjects[index]->plyFileName;
		if (!::g_pModelLoader->GetRenderingInfoByModelFileName(vec_pRenderedObjects[index]->plyFileName,
			tempPlyInfo))
		{	// Model isn't present, which is a Very Bad Thing
			continue;	// in a for loop, this will go to the next count, skipping everyint
		}
		// At this point, we have found a valid model (that was loaded)
		glBindVertexArray(tempPlyInfo.vertexBufferObjectID);					//  g_VertexPositionBufferID[1] );		// "Connects" to a vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, tempPlyInfo.vertexAttribBufferID);		//  g_VertexColourBufferID[1] );		// Also buffer (with colours)
		//glBindBuffer( GL_ARRAY_BUFFER, tempPlyInfo.vertexNormalBufferID );	
		//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, tempPlyInfo.indexBufferID );	// g_IndexBufferID[1] );	// And Index buffer	
		numberOfIndicesToRender = tempPlyInfo.numberOfElements * 3;			// g_numberOfTriangles[1] * 3; 


		glEnableVertexAttribArray(0);			// Position
		glEnableVertexAttribArray(1);			// Colour
		glEnableVertexAttribArray(2);			// Normal
		ExitOnGLError("ERROR: Could not enable vertex attributes");

		//glVertexAttribPointer(0,		// index or "slot" in the shader
		//					  4,		// Number of variables: vec4 would be 4 32-bit variables
		//					  GL_FLOAT,	// Type: vec4 is float
		//					  GL_FALSE, // "normalize" the values (or not)
		//					  sizeof(CVertex_fXYZ_fRGBA_fNxNyNzW),	// Number of bytes per vertex (the "stride")
		//					  (GLvoid*)0 );		// Offset from vertex (position is first, so offset = 0
		//ExitOnGLError("ERROR: Could not set VAO attributes");

		//// http://stackoverflow.com/questions/3718910/can-i-get-the-size-of-a-struct-field-w-o-creating-an-instance-of-the-struct
		//int offsetToColourInBytes = sizeof( ((CVertex_fXYZ_fRGBA_fNxNyNzW*)0)->Color );

		//glVertexAttribPointer(1, 
		//					  4, 
		//					  GL_FLOAT, 
		//					  GL_FALSE, 
		//					  sizeof(CVertex_fXYZ_fRGBA_fNxNyNzW), 
		//					  (GLvoid*) offsetToColourInBytes );		// Offset in bytes to Colour

		//// http://stackoverflow.com/questions/3718910/can-i-get-the-size-of-a-struct-field-w-o-creating-an-instance-of-the-struct
		//int offsetToNormalInBytes = sizeof( ((CVertex_fXYZ_fRGBA_fNxNyNzW*)0)->Normal );

		//glVertexAttribPointer(2, 
		//					  4, 
		//					  GL_FLOAT, 
		//					  GL_FALSE, 
		//					  sizeof(CVertex_fXYZ_fRGBA_fNxNyNzW), 
		//					  (GLvoid*) offsetToNormalInBytes );		// Offset in bytes to Colour

		ExitOnGLError("ERROR: Could not set VAO attributes");


		//int numberOfIndicesToRender = g_numberOfTriangles[1] * 3; 
		glDrawElements(GL_TRIANGLES,
			numberOfIndicesToRender,
			GL_UNSIGNED_INT, (GLvoid*)0);
		ExitOnGLError("ERROR: Could not draw the cube");
		// *** END of DRAW THE OBJECT FROM THE BUFFER ****

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}// for ( int index = 0...


	// Detatch from the vertex buffer (0 is reserved in OpenGL, so setting to "0" means "set to nothing", sort of)
	glBindVertexArray(0);
	// Detatch from the current shader program
	glUseProgram(0);


	::myFont.myfontload();
	if (myfontselection == 1)
	{
		::myFont.Displayfull();
	}
	else if (myfontselection == 2)
	{
		::myFont.renderCurrentLanguage();
	}
	else
	{
		::myFont.renderText();

	}

	//renderText();

	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'
	glutSwapBuffers();

	return;
}


// ***********************************************************************************
// ********************************* TOP SECRET CODE *********************************
void SetLightingUniforms(void)
{

	for (int index = 0; index < ::g_ShaderUniformVariables.MaxLights; index++)
		//	int index = 0;
	{

		glUniform1i(::g_ShaderUniformVariables.Lights[index].isEnabled_LocID, ::g_ShaderUniformVariables.Lights[index].isEnabled);
		glUniform1i(::g_ShaderUniformVariables.Lights[index].isLocal_LocID, ::g_ShaderUniformVariables.Lights[index].isLocal);
		glUniform1i(::g_ShaderUniformVariables.Lights[index].isSpot_LocID, ::g_ShaderUniformVariables.Lights[index].isSpot);

		glUniform3f(::g_ShaderUniformVariables.Lights[index].ambient_LocID, ::g_ShaderUniformVariables.Lights[index].ambient.r,
			::g_ShaderUniformVariables.Lights[index].ambient.g,
			::g_ShaderUniformVariables.Lights[index].ambient.b);

		glUniform3f(::g_ShaderUniformVariables.Lights[index].color_LocID, ::g_ShaderUniformVariables.Lights[index].color.r,
			::g_ShaderUniformVariables.Lights[index].color.g,
			::g_ShaderUniformVariables.Lights[index].color.b);

		glUniform3f(::g_ShaderUniformVariables.Lights[index].position_LocID, ::g_ShaderUniformVariables.Lights[index].position.r,
			::g_ShaderUniformVariables.Lights[index].position.g,
			::g_ShaderUniformVariables.Lights[index].position.b);

		glUniform3f(::g_ShaderUniformVariables.Lights[index].halfVector_LocID, ::g_ShaderUniformVariables.Lights[index].halfVector.r,
			::g_ShaderUniformVariables.Lights[index].halfVector.g,
			::g_ShaderUniformVariables.Lights[index].halfVector.b);

		glUniform3f(::g_ShaderUniformVariables.Lights[index].coneDirection_LocID, ::g_ShaderUniformVariables.Lights[index].coneDirection.r,
			::g_ShaderUniformVariables.Lights[index].coneDirection.g,
			::g_ShaderUniformVariables.Lights[index].coneDirection.b);

		glUniform1f(::g_ShaderUniformVariables.Lights[index].spotCosCutoff_LocID, ::g_ShaderUniformVariables.Lights[index].spotCosCutoff);

		glUniform1f(::g_ShaderUniformVariables.Lights[index].spotExponent_LocID, ::g_ShaderUniformVariables.Lights[index].spotExponent);

		glUniform1f(::g_ShaderUniformVariables.Lights[index].constantAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].constantAttenuation);

		glUniform1f(::g_ShaderUniformVariables.Lights[index].linearAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].linearAttenuation);

		glUniform1f(::g_ShaderUniformVariables.Lights[index].quadraticAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].quadraticAttenuation);

	}
	return;
}
// ********************************* TOP SECRET CODE *********************************
// ***********************************************************************************


//void renderText()
//{
//
//
//	//glUseProgram(0);
//	
//	
//	glColor3f(1.0f, 1.0f, 1.0f);
//	gl_font1.Begin();
//	
//	gl_font1.DrawString(temp, 3.0f, 0.0f, static_cast<float>(800));
//	gl_font1.DrawString("and deployment", 1.0f, 0.0f, 580);
//
//}

