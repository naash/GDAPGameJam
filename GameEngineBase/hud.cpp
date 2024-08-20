#include "hud.h"
#include "global.h"
#include <iostream>

Hud::Hud()
{
	//Initialize time and glFont
	start = time(0);
	score = 0;
	

	gameState =true;
}
Hud::~Hud()
{

}

void Hud::renderText()
{

	//////Clear back buffer
	//////glClear(GL_COLOR_BUFFER_BIT);
	//////Initialize opengl matrix. 
	////glEnable(GL_TEXTURE_2D);
	////glEnable(GL_BLEND);
	////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	////glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	////glOrtho(0.0, ::g_screenWidth, 0.0, ::g_screenHeight, 1.f, -1.f);
	//////Initialize modelview matrix
	////glMatrixMode(GL_MODELVIEW);
	////glLoadIdentity();


	//////Draw some strings
	////glColor3f(1.0f, 1.0f, 1.0f);
	////
	////_gl_font.Begin();

	////
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();

	//	glOrtho(0.0, ::g_screenWidth, 0.0, ::g_screenHeight, 1.f, -1.f);

	////Clear active shaders
	//glUseProgram(0);
	//
	//glColor4f(0.7f, 0.0f, 1.0f, 1.0f);

	//_gl_font.Begin();

	//_gl_font.DrawString("Testing", 0.5f, 0.0f, static_cast<float>(::g_screenHeight)); Wanted to display text on screen ... didnt work out :(


	//std::cout<<"Score = "<<this->score<<std::endl;
	//std::cout<<"Time left : "<<this->timeLeft<<std::endl;

	if(!gameState)
	{
	/*	if(this->score > 3)
		{
			std::cout<<"Mission Success"<<std::endl;
			system("pause");
			 exit (1);
		}
		else
		{
			std::cout<<"Bombs exploded... world ends ...good job loser :("<<std::endl;
			system("pause");
			 exit (1);
		}
	*/
	
	}

}
void Hud::updateTime()
{
	int timeNow = difftime( time(0), start);
	timeLeft = 45 - timeNow;

	if(timeLeft <= 0 || this->score > 3)
	{
	//gameState =false;
	}


}