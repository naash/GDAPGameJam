#include "fileDataLoader.h"
#include "xmlParser.h"


FileDataLoader::FileDataLoader()
{

}

FileDataLoader::~FileDataLoader()
{

}


GLuint FileDataLoader::LoadShader(const char* filename, GLenum shader_type)
{
	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	// std::string shaderSourceText;
	char* glsl_source = "\0";
	if (NULL != (file = fopen(filename, "rb")) &&
		0 == fseek(file, 0, SEEK_END) &&
		-1 != (file_size = ftell(file)))
	{
		rewind(file);

		if (NULL != (glsl_source = (char*)malloc(file_size + 1)))
		{
			if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file))
			{
				glsl_source[file_size] = '\0';

				if (0 != (shader_id = glCreateShader(shader_type)))
				{
					glShaderSource(shader_id, 1, &glsl_source, NULL);
					glCompileShader(shader_id);
					ExitOnGLError("Could not compile a shader");
				}
				else
					fprintf(stderr, "ERROR: Could not create a shader.\n");
			}
			else
				fprintf(stderr, "ERROR: Could not read file %s\n", filename);

			// free(glsl_source);
		}
		else
			fprintf(stderr, "ERROR: Could not allocate %i bytes.\n", file_size);

		fclose(file);
	}
	else
	{
		if (NULL != file)
			fclose(file);
		fprintf(stderr, "ERROR: Could not open file %s\n", filename);
	}
	GLcharARB* vShaderSource[1];
	vShaderSource[0] = glsl_source;

	//Error Checking
	::glShaderSource( shader_id,        // Handle to shader

		1,                       // Number of elements in string array (if using one big string, it's 1)

		(const GLcharARB**) vShaderSource, // Pointer to shader source (char array)

		NULL);                   // Length of array (0 or NULL if null terminated)

	// ...and compile.

	::glCompileShader(shader_id);

	//

	// Did compile work?

	GLint statusOK = 0;
	GLint isCompiled = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &statusOK);
	// ::glGetObjectParameterivARB( shader_id , GL_OBJECT_COMPILE_STATUS_ARB, &statusOK );

	if ( !statusOK )

	{

		// shaderProgDescription.vShader.vecShaderErrors.push_back("Error: Could not compile vertex shader.");

		// This gets the 'last' error message for that shader (if there was one)

		GLcharARB infoLog[ GL_INFO_LOG_LENGTH ];   // defined in glext.h

		glGetInfoLogARB( shader_id , GL_INFO_LOG_LENGTH, NULL, infoLog );

		std::stringstream ss;

		std::cout << infoLog << std::endl;

		// shaderProgDescription.vShader.vecShaderErrors.push_back( ss.str() );



	}
	else
	{
		std::cout<<"Shader compiled "<<filename<<std::endl;
	}

	return shader_id;
}



// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now
std::wstring FileDataLoader::ASCII_to_Unicode( std::string ASCIIstring )
{
	std::wstringstream ssReturnUNICODE;
	for ( std::string::iterator itChar = ASCIIstring.begin(); itChar != ASCIIstring.end(); itChar++ )
	{
		wchar_t theChar = static_cast<wchar_t>( *itChar );
		ssReturnUNICODE << theChar;
	}
	return ssReturnUNICODE.str();
}


//Loads Texture seperately 
void FileDataLoader::loadTexture(GameMediator* mediator)
{
	std::ifstream daFile("external_file/textureFile.txt");
	// Did it open?
	if (!daFile.is_open())
	{
		std::cout << "Can't open the file. Sorry it didn't work out.";
	}
	std::string temptext;

	while (daFile >> temptext)
	{
		if (temptext == "start")
			break;

	}
	int count = 0;
	while (!daFile.eof())
	{

		daFile >> modelname;


		if(modelname == "end")
			break;

		daFile >> texturePath;

		mediator->createTextures(modelname,texturePath);

		count++;	
		std::cout <<"Texture name "<< modelname <<" "<<count<<" created"<< std::endl;
	}
}


void FileDataLoader::loadXML(std::string fileName, std::string rootNode, GameMediator* mediator, CShaderUniformVariables &g_ShaderUniformVariables)
{
	// this open and parse the XML file:
	XMLNode xMainNode=XMLNode::openFileHelper(fileName.c_str(),rootNode.c_str());


	// this prints Application Name
	XMLNode xNode=xMainNode.getChildNode("Header");
	printf("Application Name is: '%s'\n", xNode.getChildNode("Application").getAttribute("name"));


	// printf("Text inside Header tag is :'%s'\n", xNode.getText());

	//Load Shaders
	xNode=xMainNode.getChildNode("Shader-data");
	int shaderCount = xNode.nChildNode("shader");

	for(int i = 0 ; i < shaderCount; i++)
	{
		ShaderBox data;
		data.shaderName = xNode.getChildNode("shader",i).getAttribute("name");

		int componentCount = xNode.getChildNode("shader",i).nChildNode("component");
		for(int k = 0 ; k < componentCount; k++)
		{
			std::string type = xNode.getChildNode("shader",i).getChildNode("component", k).getAttribute("type");
			std::string path = xNode.getChildNode("shader",i).getChildNode("component", k).getAttribute("path");

			if(type == "vertex")
			{
				data.components[GL_VERTEX_SHADER] = path;
			}
			else if(type == "fragment")
			{
				data.components[GL_FRAGMENT_SHADER] = path;
			}
			else if(type == "tes")
			{
				data.components[GL_TESS_EVALUATION_SHADER] = path;
			}
			else if(type == "tcs")
			{
				data.components[GL_TESS_CONTROL_SHADER] = path;
			}
		}



		int uniformCount = xNode.getChildNode("shader",i).nChildNode("uniform");
		for(int k = 0 ; k < uniformCount; k++)
		{
			std::string type = xNode.getChildNode("shader",i).getChildNode("uniform", k).getAttribute("type");
			std::string name = xNode.getChildNode("shader",i).getChildNode("uniform", k).getAttribute("name");

			if(type == "mat2")
			{
				data.uniformVarType[name] = UNIMAT2;
			}
			else if(type == "mat3")
			{
				data.uniformVarType[name] = UNIMAT3;
			}
			else if(type == "mat4")
			{
				data.uniformVarType[name] = UNIMAT4;
			}
			else if(type == "int")
			{
				data.uniformVarType[name] = UNIINT;
			}
			else if(type == "bool")
			{
				data.uniformVarType[name] = UNIBOOL;
			}
			else if(type == "float1")
			{
				data.uniformVarType[name] = UNIFLOAT1;
			}
			else if(type == "float2")
			{
				data.uniformVarType[name] = UNIFLOAT2;
			}
			else if(type == "float3")
			{
				data.uniformVarType[name] = UNIFLOAT3;
			}
			else if(type == "texture")
			{
				data.uniformVarType[name] = UNITEXTURE;
			}
			else if(type == "skymap")
			{
				data.uniformVarType[name] = UNISKY;
			}
		}

		mediator->createShader(data);
	}

	//Few variables that might be used later 
	Vector3D playerPos;
	//To load Textures ..............................................................................
	xNode=xMainNode.getChildNode("Texture-data");
	int textureCount = xNode.nChildNode("texture");

	for (int i=0; i<textureCount; i++)
	{
		std::string textureType = xNode.getChildNode("texture",i).getAttribute("type");
		std::string textureName = xNode.getChildNode("texture",i).getAttribute("name");
		if(textureType == "basic")
		{

			std::string texturePath = xNode.getChildNode("texture",i).getAttribute("path");
			mediator->createTextures(textureName,texturePath);
		}
		else if(textureType == "skybox")
		{
			std::vector<std::string> skybox;

			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_right"));
			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_left"));
			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_top"));
			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_bottom"));
			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_front"));
			skybox.push_back(xNode.getChildNode("texture",i).getAttribute("path_back"));

			mediator->createSkybox(skybox,textureName);
		}
	}
	//Textures loaded ..........................................................................................


	//To load Game Objects......................................................................................
	xNode=xMainNode.getChildNode("Model-data");
	int gameObjCount =  xNode.nChildNode("gameObject");


	for(int i = 0 ; i < gameObjCount; i++)
	{
		softBodyAttribs s; //------->not used
		cHavokBodyDesc rigid;
		bool altTextPresent = false;

		std::string objecType =  xNode.getChildNode("gameObject",i).getAttribute("type");
		//Name
		modelname =  xNode.getChildNode("gameObject",i).getAttribute("name");


		std::string shaderName = xNode.getChildNode("gameObject",i).getAttribute("shaderName"); //Shader name will be none if no model is specified (in case of phantoms)

		ObjectBox data;
		data.ObjectType = modelname;
		data.shaderName =shaderName;

		//Create GameObject 
		GameObject* obj = mediator->createObject(data);// ->CreateObjectByType(modelname,plypath);

		//Model flag
		temp1 = xNode.getChildNode("gameObject",i).getChildNode("model-flag").getText();
		player = std::stoi(temp1);


		if(modelname == "Sphere")
		{
			mediator->UpdateObjectRadiusByID(scale/2,obj);
		}

		if(player == 1)
		{
			mediator->setPlayerId(obj->getID());
			playerPos = position;
			obj->setAsPlayer();

			


		}
		else if(player == 2)
		{
			mediator->setSkyBoxId(obj->getID());
		}


		if(objecType != "checkpoint") //Checkpoint type doesnt have models
		{

			//Loop through all model data 
			int modelCount = xNode.getChildNode("gameObject",i).nChildNode("modelInfo");

			for(int k = 0 ; k < modelCount; k ++)
			{

				plypath =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",k).getAttribute("path");  //Path
				temp1 =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",k).getAttribute("modelMode");  //ModelType 
				
				//textureIndex= std::stoi(textIndexTemp);

				std::string textIndexTemp =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",k).getAttribute("iterations");
				int iter = std::stoi(textIndexTemp);

				temp1 =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",k).getAttribute("altTexture");

				 textIndexTemp =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",k).getAttribute("textureName"); //TextureIndex

				//For loading multiple instances of same model
				for(int j = 0 ; j < iter ; j++)
				{
					mediator->createModel(ASCII_to_Unicode(plypath),textIndexTemp,temp1 ,"rigidBody", temp1);

					obj->attachModelData(mediator->fetchModelComp().back());


				}




			}

		}
		//Loop through all physics data
		int phyCompCount = xNode.getChildNode("gameObject",i).nChildNode("physics");

		for(int j = 0 ; j < phyCompCount; j++)
		{
			physics = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("type");  //Physics Type  



			if(physics != "empty")
			{
				//Position
				std::string textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("position").getAttribute("x");
				position.x = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("position").getAttribute("y");
				position.y = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("position").getAttribute("z");
				position.z = std::stof(textIndexTemp);

				//.................
				//Rotation
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("rotation").getAttribute("x");
				rotation.x = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("rotation").getAttribute("x");
				rotation.y = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("rotation").getAttribute("z");
				rotation.z = std::stof(textIndexTemp);


				//................
				//Scale
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("scale").getText();
				scale = std::stof(textIndexTemp);   //Scale 



				if(physics == "hardBody")
				{
					temp2 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("constraint");

					if(temp2 == "enabled")
					{
						rigid.constraintEnabled = true;
					}
					else
					{
						rigid.constraintEnabled = false;
					}
					temp2 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("friction");

					rigid.Friction = atof(temp2.c_str());
					rigid.Position = position;
					rigid.Rotation = glm::quat(rotation.x,rotation.y,rotation.z,1.0f);
					rigid.scale = scale;


					std::string shape = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("shape");

					if(shape == "sphere")
					{
						rigid.shape = SPHERE;
					}
					else if(shape == "box")
					{
						rigid.shape = BOX;
						// rigid.IsStatic = true;
					}
					else if(shape == "plane")
					{
						rigid.shape = PLANE;
						rigid.IsStatic = true;
					}
					else if(shape == "complex")
					{
						rigid.shape = COMPLEX;
						rigid.IsStatic = true;
					}
					else if(shape == "chassis")
					{
						rigid.shape = CHASSIS;
					}

					rigid.enabled =true;
				}
				else if(physics == "softBody")
				{
					temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("springConst");
					s.springConst = std::stof(temp3);

					temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("indexOffset");
					s.indexOffset = std::stof(temp3);

					temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("fixedNodeList");

					if(temp3 == "range")
					{

						temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("fixedNodes");

						std::size_t found = temp3.find("-");
						int start = std::stoi(temp3.substr(0,found));
						int end = std::stoi(temp3.substr(found+1,temp3.size() -1));


						for(int k = start; k<=end; k++)
						{
							s.fixedNodes.push_back(k);
						}
					}
					else if(temp3 == "specific")
					{
						temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute("fixedNodeCount");

						int count = std::stoi(temp3);

						for(int k = 1; k <= count; k++)
						{
							std::stringstream sstm;
							sstm << "fixedNode" << k;
							std::string attr = sstm.str();
							temp3 = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getAttribute(attr.c_str());

							s.fixedNodes.push_back(std::stoi(temp3));
						}
					}
				}
				else if(physics == "phantom")
				{
				cHavokBodyDesc blank;
				rigid = blank;
				rigid.Position = position;
				rigid.Rotation = glm::quat(rotation.x,rotation.y,rotation.z,1.0f);
				rigid.scale = scale;
				rigid.enabled = false;

				//MinExtent
				std::string textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("minExtent").getAttribute("x");
				position.x = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("minExtent").getAttribute("y");
				position.y = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("minExtent").getAttribute("z");
				position.z = std::stof(textIndexTemp);


				rigid.minExtent = position;

				//MaxExtent
			    textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("maxExtent").getAttribute("x");
				position.x = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("maxExtent").getAttribute("y");
				position.y = std::stof(textIndexTemp);
				textIndexTemp = xNode.getChildNode("gameObject",i).getChildNode("physics",j).getChildNode("maxExtent").getAttribute("z");
				position.z = std::stof(textIndexTemp);

				rigid.maxExtent = position;
				
			}
				else
				{
					cHavokBodyDesc blank;
					rigid = blank;
					rigid.Position = position;
					rigid.Rotation = glm::quat(rotation.x,rotation.y,rotation.z,1.0f);
					rigid.scale = scale;
					rigid.enabled = false;

				}


			}
			else
			{
				cHavokBodyDesc blank;
				rigid = blank;
				rigid.Position = position;
				rigid.Rotation = glm::quat(rotation.x,rotation.y,rotation.z,1.0f);
				rigid.scale = scale;
				rigid.enabled = false;

			}

			if(physics != "phantom")
			{
				temp1 =  xNode.getChildNode("gameObject",i).getChildNode("modelInfo",j).getAttribute("iterations");
				int iter = std::stoi(temp1);

				for(int k=0; k < iter; k++)
				{
					mediator->AttachPhysics( obj,s ,rigid, k);


					if(player != 2 && mediator->fetchPhyComp().back()->getType() == "BASE")
					{
						obj->setWheelPosition(mediator->fetchPhyComp().back(),k);
					}
				}
			}
			else
			{
			
				mediator->AttachPhantom( obj,s ,rigid, 0);
			
			
			}



		}






	}
	//Game Objects loaded.......................................................................................


	//Loading lights............................................................................................
	xNode=xMainNode.getChildNode("Lights-data");
	int lightCount =  xNode.nChildNode("light");

	for(int i = 0 ; i < lightCount; i++)
	{
		//Light index
		std::string lightTemp =  xNode.getChildNode("light",i).getAttribute("index");
		int lightIndex = std::stoi(lightTemp);

		if(lightIndex < 15)
		{
			//Colour
			lightTemp = xNode.getChildNode("light",i).getChildNode("colour").getAttribute("red");
			float colourRed = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("colour").getAttribute("green");
			float colourGreen = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("colour").getAttribute("blue");
			float colourBlue = std::stof(lightTemp);


			//Ambient 
			lightTemp = xNode.getChildNode("light",i).getChildNode("ambient").getAttribute("red");
			float ambientRed = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("ambient").getAttribute("green");
			float ambientGreen = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("ambient").getAttribute("blue");
			float ambientBlue = std::stof(lightTemp);


			//Position 
			lightTemp = xNode.getChildNode("light",i).getChildNode("position").getAttribute("x");
			float posX = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("position").getAttribute("y");
			float posY = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("position").getAttribute("z");
			float posZ = std::stof(lightTemp);


			//Attenuation
			lightTemp = xNode.getChildNode("light",i).getChildNode("attenuation").getAttribute("constant");
			float attenC = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("attenuation").getAttribute("linear");
			float attenL = std::stof(lightTemp);
			lightTemp = xNode.getChildNode("light",i).getChildNode("attenuation").getAttribute("quadratic");
			float attenQ = std::stof(lightTemp);


			g_ShaderUniformVariables.Lights[lightIndex].isEnabled = GL_TRUE;
			g_ShaderUniformVariables.Lights[lightIndex].isLocal = GL_FALSE;		// Only directional lights AREN'T local
			g_ShaderUniformVariables.Lights[lightIndex].isSpot = GL_FALSE;		// Local = TRUE, Spot = FALSE --- Point light

			g_ShaderUniformVariables.Lights[lightIndex].color = glm::vec3(colourRed, colourGreen, colourBlue);		// White light
			g_ShaderUniformVariables.Lights[lightIndex].ambient = glm::vec3(ambientRed, ambientGreen, ambientBlue);	// White light
			g_ShaderUniformVariables.Lights[lightIndex].position = glm::vec3(posX, posY, posZ);	// Just above the origin
			g_ShaderUniformVariables.Lights[lightIndex].halfVector = glm::vec3(0.0,0.0,10.0);

			g_ShaderUniformVariables.Lights[lightIndex].constantAttenuation = attenC;
			g_ShaderUniformVariables.Lights[lightIndex].linearAttenuation = attenL;
			g_ShaderUniformVariables.Lights[lightIndex].quadraticAttenuation = attenQ;
			g_ShaderUniformVariables.Lights[lightIndex].distanceFromPlayer =g_ShaderUniformVariables.Lights[lightIndex].position - 
				glm::vec3(playerPos.x, playerPos.y,playerPos.z) ;
		}
		else
		{

			std::cout<<"Index must be below 15"<<std::endl;
		}

	}
	//Lights loaded.............................................................................................
}

void FileDataLoader::saveXML()
{
	std::cout<<"XML modifying"<<std::endl;
	// this open and parse the XML file:
	XMLNode xMainNode = XMLNode::openFileHelper("external_file/scene-bkp.xml","Scene");


}