#include "GameManager.h"
#include "GamePlayer.h"
#include "Sprite.h"
#include "Graphics.h"

void GameManager::OnStart()
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		mPlayers.push_back(new GamePlayer(rand() % 640, rand() % 480));
	}

	mBackground = Sprite::Create(L"Map", this);
	mBackground->SetPivot(0, 0);
}

void GameManager::OnFrameUpdate()
{

}

void GameManager::OnRender(Graphics* graphics)
{
	graphics->Draw(mPosition, mBackground);
}

GameManager::GameManager() 
	: GameObject(0,0)
{

}