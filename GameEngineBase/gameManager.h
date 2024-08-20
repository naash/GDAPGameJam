#ifndef _GAME_MAN
#define _GAME_MAN

#include <string>

struct PlayerData
{
	int id;
	int lapCount;
	int recentCheckpoint;
	float elapsedTime;
};



class GameManager
{
public:
	GameManager();
	~GameManager();

	void processAtCheckpoint(int checkpointId, int playerId);
	void checkLeader();

	bool isTwoPlayer;
	PlayerData player1;
	PlayerData player2;


	int leaderId;
	std::string gameStatus;

};

#endif