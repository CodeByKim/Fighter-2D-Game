#include "GamePlayer.h"
#include "Sprite.h"
#include "Graphics.h"

void GamePlayer::Start()
{

}

void GamePlayer::OnFrameUpdate()
{		
	
}

void GamePlayer::OnRender(Graphics* graphics)
{
	graphics->Draw(mPosition, mSprite);
}

GamePlayer::GamePlayer(int x, int y) 
	: GameObject(x, y)
{
	mSprite = Sprite::Create(L"Stand_R", this);
	mSprite->SetPivot(71, 90);
}