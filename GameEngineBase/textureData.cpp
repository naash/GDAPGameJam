#include "textureData.h"
#include <fstream>
#include <iostream>
#include <Windows.h>


std::vector<int> TextureData::oglTexture;
int TextureData::textIndex; 
int TextureData::fixedindex;

 void TextureData::populateTexture()
 {
	 TextureData::oglTexture.push_back(0x84C0);
	 TextureData::oglTexture.push_back(0x84C1);
	 TextureData::oglTexture.push_back(0x84C2);
	 TextureData::oglTexture.push_back(0x84C3);
     TextureData::oglTexture.push_back(0x84C4);
	 TextureData::oglTexture.push_back(0x84C5);
	 TextureData::oglTexture.push_back(0x84C6);
     TextureData::oglTexture.push_back(0x84C7);
	 TextureData::oglTexture.push_back(0x84C8);
	 TextureData::oglTexture.push_back(0x84C9);
	 TextureData::oglTexture.push_back(0x84CA);
	 TextureData::oglTexture.push_back(0x84CB);
	 TextureData::oglTexture.push_back(0x84CC);
	 TextureData::oglTexture.push_back(0x84CD);
	 TextureData::oglTexture.push_back(0x84CE);
	 TextureData::oglTexture.push_back(0x84CF);
	 TextureData::oglTexture.push_back(0x84D0);
	 TextureData::oglTexture.push_back(0x84D1);
	 TextureData::oglTexture.push_back(0x84D2);
	 TextureData::oglTexture.push_back(0x84D3);
	 TextureData::oglTexture.push_back(0x84D4);
 	 TextureData::oglTexture.push_back(0x84D5);
	 TextureData::oglTexture.push_back(0x84D6);
	 TextureData::oglTexture.push_back(0x84D7);
	 TextureData::oglTexture.push_back(0x84D8);
	 TextureData::oglTexture.push_back(0x84D9);
	 TextureData::oglTexture.push_back(0x84DA);
	 TextureData::oglTexture.push_back(0x84DB);
	 TextureData::oglTexture.push_back(0x84DC);
	 TextureData::oglTexture.push_back(0x84DD);
	 TextureData::oglTexture.push_back(0x84DE);
	 TextureData::oglTexture.push_back(0x84DF);

 }

 TextureData::TextureData()
 {
 TextureData::populateTexture();
 
 fixedindex = 30;
 
 }


TextureData::~TextureData()
{



}


bool TextureData::LoadBasicTexture(std::string fileName, std::wstring &error)
	{
	
		unsigned char * textureData;
	    unsigned int width, height;
		OpenBMPFile(fileName,textureData, width, height, error);

		
	//Now assign Buffer.........................................................................
	//Texture Loading................................................................
		glGenTextures(1, &textureID);
 
    // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
 
    // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData);
 
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering

		textureCode = TextureData::oglTexture[textIndex];
		textureNo   = textIndex;
		textIndex++ ;
		//std::cout << "texture no" << textureNo << std::endl;
	//...............................................................................
	return true;
	}


 bool TextureData::LoadEmptyTexture(GLuint &depthTextureId, GLuint &textureCode, GLuint &textureNo,  int shadowMapWidth,  int shadowMapHeight, std::string type)
 {
 
			// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);	
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	textureCode = TextureData::oglTexture[fixedindex];
	textureNo   = fixedindex;

	
 
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
 
	// TODO*: Have the depth precision be settable
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT,
		shadowMapWidth,
		shadowMapHeight,
		0,
		GL_DEPTH_COMPONENT,
		GL_UNSIGNED_BYTE,
		NULL);
	//glBindTexture(GL_TEXTURE_2D, 0);
	
		
 return true;
 }
bool TextureData::LoadSkyMapTexture(std::vector<std::string> fileName, std::wstring &error)
{

	bool bReturnVal = true;

	// Do the magic...

	// Pick a texture number...
	textureCode = TextureData::oglTexture[textIndex];
    textureNo   = textIndex;
	textIndex++ ;


	glGenTextures( 1, &textureID );
	// Worked?
	if ( ( glGetError() & GL_INVALID_VALUE ) == GL_INVALID_VALUE )
	{
		bReturnVal = false;
		return false;
	}

	//
	//glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_CUBE_MAP, textureID ); 

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
 
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE /*GL_REPEAT*/ );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE /*GL_REPEAT*/ );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE /*GL_REPEAT*/ );

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	// IF YOU DON'T GENERATE MIP MAPS, then you can use LINEAR filtering
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );	// OpenGL 4.1, maybe

				
	// Positive X image...
	// Assume all the images are the same size. If not, then it will screw up

		unsigned char * textureData;
	    unsigned int width, height;
		
	if (OpenBMPFile(fileName[0],textureData, width, height, error))
	{
		glTexStorage2D( GL_TEXTURE_CUBE_MAP, 
		            10, // Mipmap levels
					GL_RGBA8,	// Internal format
					width,	// width (pixels)
					height );		// height (pixels)
		
	}
	else
	{
		
		return false;
	}

	// Positive X image...
	glTexSubImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
		             0,   // Level
					 0, 0, // Offset
					 width,	// width
					 height,		// height
					 GL_RGB, 
					 GL_UNSIGNED_BYTE,
					 textureData );
	

	// Negative X image...
	if (OpenBMPFile(fileName[1],textureData, width, height, error))
	{
			glTexSubImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData );
	
	}
	else
	{
		
		return false;
	}
	
	// Positive Y image...
	if (OpenBMPFile(fileName[2],textureData, width, height, error))
	{
			glTexSubImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData );
	
	}
	else
	{
		
		return false;
	}

	
	// Negative Y image...
	if (OpenBMPFile(fileName[3],textureData, width, height, error))
	{
			glTexSubImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData );
	
	}
	else
	{
		
		return false;
	}


	// Positive Z image...
	if (OpenBMPFile(fileName[4],textureData, width, height, error))
	{
			glTexSubImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData );
	
	}
	else
	{
		
		return false;
	}
	
	// Negative Z image...
	if (OpenBMPFile(fileName[5],textureData, width, height, error))
	{
			glTexSubImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData );
	
	}
	else
	{
		
		return false;
	}
	

	// End of Do the magic...
	
	return bReturnVal;



}



GLuint TextureData::getTextureCode()
{
		return textureCode;
	
}

GLuint TextureData::getTextureNo()
{
		return textureNo;
	
}

GLuint TextureData::getTextureID()
{
	
		return textureID;
}

	void TextureData::setTextureName(std::string name)
	{
		textureName = name;

	}

	 bool TextureData::OpenBMPFile(std::string fileName,unsigned char * &p_textureData, unsigned int &p_width, unsigned int &p_height, std::wstring &error)
    {

				unsigned char header[54]; // Each BMP file begins by a 54-bytes header
			unsigned int dataPos;     // Position in the file where the actual data begins
			
			unsigned int imageSize;   // = width*height*3
// Actual RGB data
			

			FILE * theBMPFile = fopen(fileName.c_str(),"rb");
	
		if (!theBMPFile)
		{
		error = L"Can't open the file. Sorry it didn't work out.";
		return false;
		}


		if ( fread(header, 1, 54, theBMPFile)!=54 )
		{ // If not 54 bytes read : problem
		 error = L"Not a correct BMP file" ;
		  return false;
         }

		if ( header[0]!='B' || header[1]!='M' ){
			error = L"Not a correct BMP file";
		    return 0;
		}

		// Read ints from the byte array
		dataPos    = *(int*)&(header[0x0A]);
		imageSize  = *(int*)&(header[0x22]);
		p_width      = *(int*)&(header[0x12]);
		p_height     = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=p_width*p_height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	p_textureData = new unsigned char [imageSize];
 
	// Read the actual data from the file into the buffer
	fread(p_textureData,1,imageSize,theBMPFile);
 
	//Everything is in memory now, the file can be closed
	fclose(theBMPFile);
	
	 
	 }


