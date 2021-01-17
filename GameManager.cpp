#include "GameManager.h"
#include "GamePlayer.h"
#include "Sprite.h"
#include "Graphics.h"

void GameManager::OnStart()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 1; i++)
	{
		mPlayers.push_back(new GamePlayer(0, rand() % 480));
	}

	//mBackground = Sprite::Create(L"Map", this);
	//mBackground->SetPivot(0, 0);
}

void GameManager::OnFrameUpdate()
{

}

void GameManager::OnRender(Graphics* graphics)
{
	//graphics->Draw(mPosition, mBackground);
}

GameManager::GameManager() 
	: GameObject(0,0), mBackground(nullptr)
{

}