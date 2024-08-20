#include "gameManager.h"

#include <iostream>

GameManager::GameManager()
{
	//Initializing 
	isTwoPlayer = false;
	player1.id = -1;
	player1.lapCount = 0;
	player1.recentCheckpoint = 1;
	player1.elapsedTime = 0.0f;

	player2.id = -1;
	player2.lapCount = 0;
	player2.recentCheckpoint = 1;
	player2.elapsedTime = 0.0f;


	gameStatus = "STARTED";
};


GameManager::~GameManager()
{


}

void GameManager::processAtCheckpoint(int checkpointId, int playerId)
{
	if(playerId == player1.id)
	{
		if(checkpointId == 2 && player1.recentCheckpoint == 1)
		{
			player1.recentCheckpoint = 2;
		}
		else if(checkpointId == 1 && player1.recentCheckpoint == 2)
		{
			player1.recentCheckpoint = 1;
			player1.lapCount++;
		}
		else
		{
			std::cout<<"Wrong direction"<<std::endl;
			
		}
	
	
	}
	else if(playerId == player2.id)
	{
		if(checkpointId == 2 && player2.recentCheckpoint == 1)
			{
				player2.recentCheckpoint = 2;
			}
			else if(checkpointId == 1 && player2.recentCheckpoint == 2)
			{
				player2.recentCheckpoint = 1;
				player2.lapCount++;
			}
			else
			{
				std::cout<<"Wrong direction"<<std::endl;
			}
	}


}

void GameManager::checkLeader()
{
	if(isTwoPlayer)
	{
		if(player1.lapCount > player2.lapCount)
		{
			//Player 1 leads OBV
			this->leaderId = player1.id;
		}
		else if(player1.lapCount < player2.lapCount)
		{
			//Player 2 leads OBV
			this->leaderId = player2.id;
		}
		else
		{
		//Lap count is same , check last checkpoint crossed
			if(player1.recentCheckpoint > player2.recentCheckpoint)
			{
			//Player 1 leads OBV
			this->leaderId = player1.id;
			}
			else if(player1.recentCheckpoint < player2.recentCheckpoint)
			{
			//Player 2 leads OBV
			this->leaderId = player2.id;
			}
			else
			{
			//Everything is same
			
			}
		
		
		}
	
	}
	else
	{
		//Single player so he will always be the leader
		this->leaderId = player1.id;


	}

}