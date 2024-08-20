#ifndef _TEXTURE_D
#define _TEXTURE_D

#include <vector>
#include <glew.h>
#include <string>
class TextureData
{
public:
	TextureData();
	~TextureData();

	enum enumTEXCOORDBIAS
	{
		POSITIVE_X, POSITIVE_Y, POSITIVE_Z
	};


	void setTextureName(std::string name);

	//Open Texture 
    bool OpenBMPFile(std::string fileName,unsigned char * &p_textureData, unsigned int &p_width, unsigned int &p_height, std::wstring &error);

   bool LoadBasicTexture(std::string fileName, std::wstring &error);    //Opens BMP File and Assigns Buffer to it 
  static bool LoadEmptyTexture(GLuint &textureID, GLuint &textureCode, GLuint &textureNo,  int p_width,  int p_height, std::string type);
   //Load Texture for skymap
   bool LoadSkyMapTexture(std::vector<std::string> fileName, std::wstring &error);  //Opens 6 BMP File and Assigns Buffer to it 

   GLuint getTextureID();
	GLuint getTextureCode();
	GLuint getTextureNo();

	

   
   //Populates oglTexture 
   static void populateTexture();

   static int textIndex;
   static int fixedindex;


private:
	
	std::string textureName ;
	

	static std::vector<int> oglTexture;
	GLuint textureID;
	int textureCode ;
	int textureNo ;



};


#endif