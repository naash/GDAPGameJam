#pragma once


#include <pugixml.hpp>
#include <map>
#include <vector>
#include <sstream>
#include <gl/glew.h>
#include "CGameObject.h"
#include "CCamera.h"
#include "glfont2.h"
enum eLanguage
{
	LANGUAGE_ENGLISH = 0,
	LANGUAGE_FRENCH,
	LANGUAGE_SPANISH,
	LANGUAGE_HINDI,
	LANGUAGE_NONE
};

enum eText
{
	STRING_1 = 0,
	STRING_2,
	STRING_3,
	STRING_4,
	STRING_5,
	STRING_6,
	STRING_7,
	STRING_8,
	STRING_9,
	STRING_10,
	STRING_11,
	STRING_12,
	STRING_13,
	STRING_14,
	STRING_15,
	STRING_16,
	STRING_17,
	STRING_18,
	STRING_19,
	STRING_20,
	
};

class LangXml
{
public:
	LangXml();
	~LangXml();
	void loadLanguange();
	void renderText();
	void renderCurrentLanguage();


	void MyfontCreate();
	void myfontload();
	void DisplayPosition(CVector3f pos,CVector3f rot,float scale,std::string modelname,std::string filepath);
	void CameraAttributes(float ex, float ey, float ez, float upx, float upy);
	void SceneSaved(bool value);
	void GamePaused(bool Value);
	void Displayfull();
	void SwitchLang(int i);
	std::wostringstream ws;

	std::map<eLanguage, std::vector<std::wstring>> _mapLanguage;

	eLanguage _currentLanguage = LANGUAGE_ENGLISH;
	int _windowHeight;
	glfont::GLFont gl_font1;
	std::string posx;
	std::string posy;
	std::string posz;
	
	std::string rotx;
	std::string roty;
	std::string rotz;


	std::string modelname;
	std::string pathofmodel;
	std::string scale;
	std::string saved;




	/********************Camera**************/
	std::string eyex;
	std::string eyey;
	std::string eyez;
	std::string camposx;
	std::string camposy;













};

