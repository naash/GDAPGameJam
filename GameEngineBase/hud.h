#ifndef _HUD_H
#define _HUD_H

#include <time.h>



class Hud
{
public:
	Hud();
	~Hud();

	void renderText();
	void updateTime();
	int score;
	int timeLeft;
	bool gameState;
	time_t start;

};

#endif