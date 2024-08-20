#include "global.h"
#include "XmlUpdate.h"
bool wireval = false;
int i = 0;
bool halt = false;
void glutKeyboard_callback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':		// Space
	{
						CMessage theMessage;
						theMessage.vecNVPairs.push_back(CNameValuePair("StopMoving"));
						::g_pFactoryMediator->SendMessageToObject(g_Player_ID, 0, theMessage);
	}
		break;



	case 'a': case 'A':
		if (halt == false)
		{
			::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
			myFont.CameraAttributes(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z, g_pCamera->up.x, g_pCamera->up.y);
			::myFont.SceneSaved(false);
		}
		break;
	case 'd': case 'D':
		if (halt == false)
		{
			::g_pCamera->eye.x += 0.1f;		// Right (+ve x)
			myFont.CameraAttributes(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z, g_pCamera->up.x, g_pCamera->up.y);
			::myFont.SceneSaved(false);
		}
		break;
	case 'w': case 'W':
		if (halt == false)
		{
			::g_pCamera->eye.z -= 0.1f;		// Forward (-ve z)
			myFont.CameraAttributes(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z, g_pCamera->up.x, g_pCamera->up.y);
			::myFont.SceneSaved(false);
		}break;
	case 'x': case 'X':
		if (halt == false)
		{
			::g_pCamera->eye.z += 0.1f;		// Back (-ve z)
			myFont.CameraAttributes(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z, g_pCamera->up.x, g_pCamera->up.y);
			::myFont.SceneSaved(false);
		}break;

	case 'n':case 'N':
		if (halt == false)
		{
			{
				if (::g_ShaderUniformVariables.Lights[2].isEnabled == GL_TRUE){
					::g_ShaderUniformVariables.Lights[2].isEnabled = GL_FALSE;
				}
				else
				{
					::g_ShaderUniformVariables.Lights[2].isEnabled = GL_TRUE;

				}


			}
		}
		break;
	case 'm':case'M':
		if (halt == false)
		{
			{
				if (::g_ShaderUniformVariables.Lights[0].isEnabled == GL_TRUE){
					::g_ShaderUniformVariables.Lights[0].isEnabled = GL_FALSE;
				}
				else
				{
					::g_ShaderUniformVariables.Lights[0].isEnabled = GL_TRUE;

				}


			}
		}break;
	case'c':case'C':
		if (halt == false)
		{
			{
				if (::g_ShaderUniformVariables.Lights[3].isEnabled == GL_TRUE){
					::g_ShaderUniformVariables.Lights[3].isEnabled = GL_FALSE;
				}
				else
				{
					::g_ShaderUniformVariables.Lights[3].isEnabled = GL_TRUE;

				}


			}
		}
		break;
	case'`':case'~':
		if (halt == false)
		{
			{
				wireval = (!wireval);
			}
		}
		break;



	case 's':case 'S':
		if (halt == false)
		{
			{
				XmlUpdate myobj;
				myobj.CameraXmlUpdate();
				myobj.SceneXmlUpdate();
				::myFont.SceneSaved(true);


			}
		}
		break;

	case 'f':case 'F':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);
				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);
				i++;
				if (i + 1 > vec_pGameObjects.size())
					i = 0;

			}
		}
		break;


	case 'i':case 'I':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.y += 0.1f;
				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);



			}
		}
		break;
	case 'j':case 'J':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.x -= 0.1f;

				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);


			}
		}
		break;
	case 'l':case 'L':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.x += 0.1f;

				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);


			}
		}
		break;
	case 'k':case 'K':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.y -= 0.1f;
				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);



			}
		}
		break;
	case 'o':case 'O':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.z -= 0.1f;

				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);


			}
		}
		break;
	case 'u':case 'U':
		if (halt == false)
		{
			{
				std::vector< CGameObject* > vec_pGameObjects;
				g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

				vec_pGameObjects[i]->position.z += 0.1f;
				CGameObject* temp = vec_pGameObjects[i];

				::myFont.DisplayPosition(temp->position, temp->rotation, temp->scale, temp->name, temp->plyFileName);

				::myFont.SceneSaved(false);



			}
		}
		break;

	case 'p':case 'P':
	{
				 if (halt == false)
				 {
					 myfontselection = 2;
				 }
				 else
				 {
					 myfontselection = 1;
				 }
				 halt = !halt;
	}

		break;
	case '1':
		if (halt == false)
		{
			{
				myfontselection = 1;
				myFont.SwitchLang(0);



			}
		}
		break;
	case '2':
		if (halt == false)
		{
			{
				myfontselection = 1;
				myFont.SwitchLang(1);




			}
		}
		break;
	case '3':
		if (halt == false)
		{
			{
				myfontselection = 1;
				myFont.SwitchLang(2);




			}
		}
		break;
	case '4':
		if (halt == false)
		{
			{
				myfontselection = 1;
				myFont.SwitchLang(3);




			}
		}
		break;


	};
	return;
}
