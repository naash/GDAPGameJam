// Some code originally from : http://openglbook.com/the-book.html 

// Comments are from Michael Feeney (mfeeney(at)fanshawec.ca)

////**************PugiXml***********/////
#include "pugixml.hpp"
///////*******************//////////////





#include "global.h"


#define WINDOW_TITLE_PREFIX "Chapter 4"
#include <iostream>		
#include <sstream>		

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "CHRTimer.h"


CHRTimer g_simTimer;
unsigned int ID;

std::string modelname;
std::string plypath;
float rotx, roty, rotz;
float posx, posy, posz;
float scale;
float colr, colg, colb;



void LoadShaders(void);


int main(int argc, char* argv[])
{
	while (true)
	{
		pugi::xml_document doc;
		std::vector<std::string> LoadXMlDocuments;
		LoadXMlDocuments.push_back("XmlFiles/easy.xml");
		LoadXMlDocuments.push_back("XmlFiles/medium.xml");
		LoadXMlDocuments.push_back("XmlFiles/hard.xml");

		for (int i = 0; i < LoadXMlDocuments.size(); i++)
		{

			pugi::xml_parse_result result = doc.load_file(LoadXMlDocuments[i].c_str());

			if (result)
			{
				std::cout << "XML loaded succesfully!" << std::endl;
			}
			else
			{
				std::cout << "Error, Unable to load XML file!" << std::endl;

				return -1;
			}

		}

		printTheWhatsThisProgramAboutBlurb();
		///**************************XML code Insertion*************/////////
		_xmlFileName = LoadXMlDocuments[0];

		while (true)
		{
			int value = 0;

			std::cout << "Please enter the Choice for Xml File by Pressing 1,2,3 for File easy, medium and Hard" << std::endl;
			std::cin >> value;
			switch (value)
			{
			case 1:
				_xmlFileName = LoadXMlDocuments[0];
				std::cout << "File Selected Easy" << std::endl;
				break;
			case 2:
				_xmlFileName = LoadXMlDocuments[1];
				std::cout << "File Selected Medium" << std::endl;
				break;
			case 3:
				_xmlFileName = LoadXMlDocuments[2];
				std::cout << "File Selected Hard" << std::endl;
				break;
			default:
				std::cout << "There are only 3 files Press 1,2,3 to access them" << std::endl;
				break;

			};
			break;
		}



		/////////////////*******************End OIf checking File Existence*********//////

		::OpenGL_Initialize(argc, argv, 1200, 800);

		LoadShaders();


		g_pModelLoader = new CModelLoaderManager();

		std::vector<CVertex_fXYZW> colors;
		CVertex_fXYZW color;
		std::vector< std::string > vecModelsToLoad;

		/************************XML Parsing and retrieving Info for Model*****************************/

		doc.load_file(_xmlFileName.c_str());
		pugi::xml_node plyfiles = doc.child("ConfigSettings").child("PlyFiles");

		for (pugi::xml_node_iterator it = plyfiles.begin(); it != plyfiles.end(); it++)
		{
			for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
			{
				std::string temp;
				temp = ait->name();
				if (temp == "PlyFilePath")
					plypath = ait->value();
				if (temp == "colr")
					colr = ait->as_float();
				if (temp == "colb")
					colb = ait->as_float();
				if (temp == "colg")
					colg = ait->as_float();
			}
			vecModelsToLoad.push_back(plypath);
			color.SetParams(colr, colb, colg);
			colors.push_back(color);
		}
		if (!g_pModelLoader->LoadModels(vecModelsToLoad, colors))
		{
			std::cout << "Can't load one or more models. Sorry it didn't work out." << std::endl;
			return -1;
		}
		/*********************************************************************/

		::g_SetShaderUniformVariables();

		g_pFactoryMediator = new CFactoryMediator();


		std::string temptext;
		CPlyInfo tempPlyInfo;
		/////////////********************Loading Scene from Xml***************//////////
		pugi::xml_node scene = doc.child("ConfigSettings").child("Scene");

		for (pugi::xml_node_iterator it = scene.begin(); it != scene.end(); it++)
		{
			for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
			{
				std::string temp;
				temp = ait->name();
				if (temp == "ModelName")
					modelname = ait->value();
				if (temp == "PlyFilePath")
					plypath = ait->value();
				if (temp == "rotx")
					rotx = ait->as_float();
				if (temp == "roty")
					roty = ait->as_float();
				if (temp == "rotz")
					rotz = ait->as_float();
				if (temp == "posx")
					posx = ait->as_float();
				if (temp == "posy")
					posy = ait->as_float();
				if (temp == "posz")
					posz = ait->as_float();
				if (temp == "scale")
					scale = ait->as_float();
			}

			ID = g_pFactoryMediator->CreateObjectByType(modelname, plypath);
			g_pFactoryMediator->UpdateObjectRotationByID(ID, CVector3f(rotx, roty, rotz));
			//g_pFactoryMediator->UpdateColourByID(ID, CVector3f(colr,colg,colb));
			g_pFactoryMediator->UpdateObjectPositionByID(ID, CVector3f(posx, posy, posz));
			g_pModelLoader->GetRenderingInfoByModelFileName(plypath, tempPlyInfo);
			g_pFactoryMediator->UpdateObjectScaleByID(ID, scale / tempPlyInfo.extent);
		}

		//////////*****************************Ending of Scene XML loop*************/////////




		g_pCamera = new CCamera();

		g_pCamera->SetMediator((IMediator*)g_pFactoryMediator);

		/****************************************Loading camera from Xml******************/
		pugi::xml_node camera = doc.child("ConfigSettings").child("Camera");

		for (pugi::xml_node_iterator it = camera.begin(); it != camera.end(); it++)
		{
			float eyex, eyey, eyez, upx, upy;
			for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
			{
				std::string temp;
				temp = ait->name();
				if (temp == "eyex")
					eyex = ait->as_float();
				if (temp == "eyey")
					eyey = ait->as_float();
				if (temp == "eyez")
					eyez = ait->as_float();
				if (temp == "upx")
					upx = ait->as_float();
				if (temp == "upy")
					upy = ait->as_float();
			}
			g_pCamera->eye.x = eyex;
			g_pCamera->eye.y = eyey;
			g_pCamera->eye.z = eyez;

			g_pCamera->up.x = upx;
			g_pCamera->up.y = upy;
		}
		/*******************************************************/
		/****************************************Loading Lights from Xml******************/

		pugi::xml_node light = doc.child("ConfigSettings").child("Light");

		for (pugi::xml_node_iterator it = light.begin(); it != light.end(); it++)
		{
			float colr, colb, colg, ambx, amby, ambz, posx, posy, posz, ca, la, qa;
			int i;
			for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
			{
				std::string temp;
				temp = ait->name();
				if (temp == "LightNumber")
					i = ait->as_int();
				if (temp == "colr")
					colr = ait->as_float();
				if (temp == "colb")
					colb = ait->as_float();
				if (temp == "colg")
					colg = ait->as_float();
				if (temp == "ambx")
					ambx = ait->as_float();
				if (temp == "amby")
					amby = ait->as_float();
				if (temp == "ambz")
					ambz = ait->as_float();
				if (temp == "posx")
					posx = ait->as_float();
				if (temp == "posy")
					posy = ait->as_float();
				if (temp == "posz")
					posz = ait->as_float();
				if (temp == "ca")
					ca = ait->as_float();
				if (temp == "la")
					la = ait->as_float();
				if (temp == "qa")
					qa = ait->as_float();


			}



			::g_ShaderUniformVariables.Lights[i].isEnabled = GL_TRUE;
			::g_ShaderUniformVariables.Lights[i].isLocal = GL_TRUE;
			::g_ShaderUniformVariables.Lights[i].isSpot = GL_FALSE;

			::g_ShaderUniformVariables.Lights[i].color = glm::vec3(colr, colg, colb);
			::g_ShaderUniformVariables.Lights[i].ambient = glm::vec3(ambx, amby, ambz);
			::g_ShaderUniformVariables.Lights[i].position = glm::vec3(posx, posy, posz);


			::g_ShaderUniformVariables.Lights[i].constantAttenuation = ca;
			::g_ShaderUniformVariables.Lights[i].linearAttenuation = la;
			::g_ShaderUniformVariables.Lights[i].quadraticAttenuation = qa;
		}


		/*******************************************************/

		// Added in animation on Sept 19
		g_simTimer.Reset();
		g_simTimer.Start();		// Start "counting"

		glutMainLoop();

		//****************** Checking for Exiting or Not**********************///////////////
		std::cout << "Press Any Key to continue or Enter 'Q' or 'q' to Exit" << std::endl;
		char ExitBool;
		std::cin >> ExitBool;
		if (ExitBool == 'q' || ExitBool == 'Q')
			break;
	}

	exit(EXIT_SUCCESS);
}


static const float g_MAXIMUM_TIME_STEP = 0.1f;		// 10th of a second or 100ms 

void IdleFunction(void)
{
	// Update the "simulation" at this point.
	// 1. Get elapsed time
	g_simTimer.Stop();
	float deltaTime = ::g_simTimer.GetElapsedSeconds();
	// Is the number TOO big (we're in a break point or something?)
	if (deltaTime > g_MAXIMUM_TIME_STEP)
	{	// Yup, so clamp it to a new value
		deltaTime = g_MAXIMUM_TIME_STEP;
	}
	g_simTimer.Start();

	// Set the light at the same location as the player object...
	CVector3f playerLocation;
	g_pFactoryMediator->GetPositionByID(::g_Player_ID, playerLocation);



	std::vector< CGameObject* > vec_pGameObjects;
	g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

	for (int index = 0; index != static_cast<int>(vec_pGameObjects.size()); index++)
	{
		vec_pGameObjects[index]->position.x += (vec_pGameObjects[index]->velocity.x * deltaTime);
		vec_pGameObjects[index]->position.y += (vec_pGameObjects[index]->velocity.y * deltaTime);
		vec_pGameObjects[index]->position.z += (vec_pGameObjects[index]->velocity.z * deltaTime);
	}

	for (int index = 0; index != static_cast<int>(vec_pGameObjects.size()); index++)
	{
		vec_pGameObjects[index]->Update(deltaTime);
	}





	::g_pCamera->Update(deltaTime);


	glutPostRedisplay();
	return;
}

void TimerFunction(int Value)
{
	if (0 != Value)
	{


		std::stringstream ss;
		ss << WINDOW_TITLE_PREFIX << ": "
			<< ::g_FrameCount * 4 << " Frames Per Second @ "
			<< ::g_screenWidth << " x"				// << CurrentWidth << " x "
			<< ::g_screenHeight;					// << CurrentHeight;

		glutSetWindowTitle(ss.str().c_str());
		//glutSetWindowTitle(TempString);
		//free(TempString);
	}

	::g_FrameCount = 0;	// FrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);

	return;
}

void LoadShaders(void)
{
	//g_ShaderIds[0] = glCreateProgram();
	// A "Shader Program" is a container to hold a "set" of shaders
	// (at least a vertex and a fragment shader, but possibly more)
	g_ShaderProgram_ID = glCreateProgram();


	ExitOnGLError("ERROR: Could not create the shader program");

	//g_ShaderIds[2] = LoadShader("SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
	//g_VertexShader_ID = LoadShader("shaders/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
	g_VertexShader_ID = LoadShader("shaders/OpenGLProgGuidMutipleLights.vertex.glsl", GL_VERTEX_SHADER);

	//g_ShaderIds[1] = LoadShader("SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	//g_FragmentShader_ID = LoadShader("shaders/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	g_FragmentShader_ID = LoadShader("shaders/OpenGLProgGuidMutipleLights.fragment.glsl", GL_FRAGMENT_SHADER);


	// Now we associate these specific COMPILED shaders to the "program"...
	//glAttachShader(g_ShaderIds[0], g_ShaderIds[1]);
	glAttachShader(g_ShaderProgram_ID, g_VertexShader_ID);
	//glAttachShader(g_ShaderIds[0], g_ShaderIds[2]);
	glAttachShader(g_ShaderProgram_ID, g_FragmentShader_ID);

	// Just like when "building" in C or C++, there is a compile, followed by a link phase...
	// This will take the two compiled shaders and link them to a shader "program".
	// At this point, all the uniform variables will be assigned "slots".
	// (in other words, you can't "find" the uniform variables until you link)

	//glLinkProgram(g_ShaderIds[0]);
	glLinkProgram(g_ShaderProgram_ID);

	ExitOnGLError("ERROR: Could not link the shader program");


	return;
}



