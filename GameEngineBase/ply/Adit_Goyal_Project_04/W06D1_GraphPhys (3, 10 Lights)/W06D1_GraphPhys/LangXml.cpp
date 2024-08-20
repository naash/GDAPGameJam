#include "LangXml.h"


LangXml::LangXml()
{

	_windowHeight = 800;
	posx = "N/A";
	posy = "N/A";
	posz = "N/A";
	rotx = "N/A";
	roty = "N/A";
	rotz = "N/A";
	scale = "N/A";
	modelname = "N/A";
	pathofmodel = "N/A";

	camposx = "N/A";
	camposy = "N/A";
	eyex = "N/A";
	eyey = "N/A";
	eyez = "N/A";
	saved = "N/A";
}

void LangXml::MyfontCreate()
{
	gl_font1.Create("XmlFiles/arial22Font.glf", 1);
}




void LangXml::myfontload()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1200, 0.0, 800, 5, -5);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
void LangXml::loadLanguange()
{
	//Load xml file
	std::wstring xmlLanguageFileName = L"XmlFiles/localization.xml";

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(xmlLanguageFileName.c_str());

	

	pugi::xml_node languages = doc.child("Localization");

	

	for (pugi::xml_node_iterator it = languages.begin(); it != languages.end(); it++)
	{

		//Loop attributes
		for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
		{
			ws.str(L"");
			ws << ait->value();
			if (ws.str() == L"EN")
			{
				ws.str(L"");
				ws << it->child("String_1").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_2").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_3").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_4").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_5").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_6").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_7").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_8").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_9").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_10").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_11").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_12").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_13").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_14").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_15").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_16").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_17").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_18").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_19").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_20").child_value();
				_mapLanguage[LANGUAGE_ENGLISH].push_back(ws.str());
			}
			else if (ws.str() == L"FR")
			{
				ws.str(L"");
				ws << it->child("String_1").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_2").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_3").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_4").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_5").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_6").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_7").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_8").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_9").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_10").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_11").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_12").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_13").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_14").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_15").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_16").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_17").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_18").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_19").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_20").child_value();
				_mapLanguage[LANGUAGE_FRENCH].push_back(ws.str());
			}
			else if (ws.str() == L"SP")
			{
				ws.str(L"");
				ws << it->child("String_1").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_2").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_3").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_4").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_5").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_6").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_7").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_8").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_9").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_10").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_11").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_12").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_13").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_14").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_15").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_16").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_17").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_18").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_19").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_20").child_value();
				_mapLanguage[LANGUAGE_SPANISH].push_back(ws.str());
			}
			else if (ws.str() == L"HI")
			{
				ws.str(L"");
				ws << it->child("String_1").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_2").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_3").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_4").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_5").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_6").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_7").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_8").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_9").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_10").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_11").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_12").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_13").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_14").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_15").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_16").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_17").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_18").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_19").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
				ws.str(L"");
				ws << it->child("String_20").child_value();
				_mapLanguage[LANGUAGE_HINDI].push_back(ws.str());
			}
		}
	}

}

LangXml::~LangXml()
{
}


void LangXml::renderText()
{
	//Clear active shaders

	glUseProgram(0);
	GLfloat yOffset = 80.0f;

	glColor3f(1.0f, 1.0f, 1.0f);
	gl_font1.Begin();
	gl_font1.DrawString("Press - key 1 - for - ENGLISH", 1.0f, 0.0f, static_cast<float>(_windowHeight));
	gl_font1.DrawString("Press - key 2 - for - FRENCH", 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset));
	gl_font1.DrawString("Press - key 3 - for - SPANISH", 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 2));
	gl_font1.DrawString("Press - key 4 - for - HINDI", 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 3));
	

}


void LangXml::renderCurrentLanguage()
{
	//Clear active shaders
	glUseProgram(0);

	GLfloat yOffset = 80.0f;

	glColor3f(1.0f, 1.0f, 1.0f);
	gl_font1.Begin();
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_1], 1.0f, 0.0f, static_cast<float>(_windowHeight));
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_2], 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 2));
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_3], 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 3));
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_4], 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 4));
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_5], 1.0f, 0.0f, static_cast<float>(_windowHeight)-(yOffset * 5));
}


void LangXml::DisplayPosition(CVector3f pos, CVector3f rot, float scaleofmodel, std::string model, std::string filepath)

{
	
	posx = std::to_string(pos.x);
	posy = std::to_string(pos.y);
	posz = std::to_string(pos.z);

	rotx = std::to_string(rot.x);
	roty = std::to_string(rot.y);
	rotz = std::to_string(rot.z);

	modelname = model;
	pathofmodel =filepath;
	scale = std::to_string(scaleofmodel);
}

void LangXml::CameraAttributes(float ex,float ey,float ez,float upx,float upy)
{
	 eyex=std::to_string(ex);
	 eyey = std::to_string(ey);
	 eyez = std::to_string(ez);
	 camposx = std::to_string(upx);
	 camposy = std::to_string(upy);

}

void LangXml::SceneSaved(bool value)
{

	if (value == true)
		saved = "Yes";
	else
		saved = "NO";


}

void LangXml::GamePaused(bool value)
{
	if (value == true)
		renderCurrentLanguage();
}

void LangXml::Displayfull()
{
	int xOffset = 250.0f;
	int yOffset = 40.0f;

	gl_font1.Begin();
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_6], 1.0f, 0.0f, 800);
	gl_font1.DrawString(eyex.c_str(), 1.0f, xOffset, 800);

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_7], 1.0f, 0.0f, 800 - yOffset);
	gl_font1.DrawString(eyey.c_str(), 1.0f, xOffset, 800 - yOffset);

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_8], 1.0f, 0.0f, 800-(yOffset * 2));
	gl_font1.DrawString(eyez.c_str(), 1.0f, xOffset, 800 - (yOffset * 2));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_9], 1.0f, 0.0f, 800 - (yOffset * 3));
	gl_font1.DrawString(camposx.c_str(), 1.0f, xOffset, 800 - (yOffset * 3));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_10], 1.0f, 0.0f, 800 - (yOffset * 4));
	gl_font1.DrawString(camposy.c_str(), 1.0f, xOffset, 800 - (yOffset * 4));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_18], 1.0f, 0.0f, 800 - (yOffset * 5));
	gl_font1.DrawString(modelname.c_str(), 1.0f, xOffset, 800 - (yOffset * 5));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_19], 1.0f, 0.0f, 800 - (yOffset * 6));
	gl_font1.DrawString(pathofmodel.c_str(), 1.0f, xOffset, 800 - (yOffset * 6));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_20], 1.0f, 0.0f, 800 - (yOffset * 7));
	gl_font1.DrawString(saved.c_str(), 1.0f, xOffset, 800 - (yOffset * 7));
	/************************************************************************************************************/
	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_11], 1.0f, 800.0, 800 - (yOffset));
	gl_font1.DrawString(posx.c_str(), 1.0f, (800.0+xOffset), 800 - (yOffset));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_12], 1.0f, 800.0, 800 - (yOffset * 2));
	gl_font1.DrawString(posy.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 2));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_13], 1.0f, 800.0, 800 - (yOffset * 3));
	gl_font1.DrawString(posz.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 3));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_14], 1.0f, 800.0, 800 - (yOffset * 4));
	gl_font1.DrawString(rotx.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 4));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_15], 1.0f, 800.0, 800 - (yOffset * 5));
	gl_font1.DrawString(roty.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 5));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_16], 1.0f, 800.0, 800 - (yOffset * 6));
	gl_font1.DrawString(rotz.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 6));

	gl_font1.DrawString(_mapLanguage[_currentLanguage][(GLuint)STRING_17], 1.0f, 800.0, 800 - (yOffset * 7));
	gl_font1.DrawString(scale.c_str(), 1.0f, (800.0 + xOffset), 800 - (yOffset * 7));







}


void LangXml::SwitchLang(int i)
{
	if (i == 0)
	{
		_currentLanguage = LANGUAGE_ENGLISH;
	}
	else if (i == 1)
	{
		_currentLanguage = LANGUAGE_FRENCH;
	}
	else if (i == 2)
	{
		_currentLanguage = LANGUAGE_SPANISH;
	}
	else if (i==3)
	{
		_currentLanguage = LANGUAGE_HINDI;
	}
	else
	{
	}
}