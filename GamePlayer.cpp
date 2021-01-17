#include "GamePlayer.h"
#include "SpriteAnimation.h"
#include "Graphics.h"

void GamePlayer::OnStart()
{
	//mSprite = Sprite::Create(L"Stand_R", this);
	//mSprite->SetPivot(71, 90);

	mAnimation = new SpriteAnimation();
	mAnimation->AddAnimation(L"Attack1_R", this, 5);
}

void GamePlayer::OnFrameUpdate()
{				
	mAnimation->Play(L"Attack1_R");
}

void GamePlayer::OnRender(Graphics* graphics)
{	
	graphics->Draw(mPosition, mAnimation->GetCurrentSprite());
}

GamePlayer::GamePlayer(int x, int y) 
	: GameObject(x, y), mAnimation(nullptr)
{	
}