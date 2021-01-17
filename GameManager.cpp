#include "GameManager.h"
#include "GamePlayer.h"

void GameManager::OnStart()
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		mPlayers.push_back(new GamePlayer(rand() % 640, rand() % 480));
	}
}

void GameManager::OnFrameUpdate()
{

}

void GameManager::OnRender(Graphics* graphics)
{
	
}

GameManager::GameManager() 
	: GameObject(0,0)
{

}