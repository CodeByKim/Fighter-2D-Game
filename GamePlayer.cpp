#include "GamePlayer.h"
#include "SpriteAnimation.h"
#include "Graphics.h"

void GamePlayer::OnStart()
{
	//mSprite = Sprite::Create(L"Stand_R", this);
	//mSprite->SetPivot(71, 90);

	mAnimation = new SpriteAnimation();
	mAnimation->AddAnimation(L"Move_R", this, 4);
	mAnimation->AddAnimation(L"Move_L", this, 4);
	mAnimation->AddAnimation(L"Stand_R", this, 3);
}

void GamePlayer::OnFrameUpdate()
{	
	if (GetAsyncKeyState(VK_UP))
	{
		mPosition.y -= 2;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		mPosition.y += 2;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		mAnimation->Play(L"Move_L");
		mPosition.x -= 2;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		mAnimation->Play(L"Move_R");
		mPosition.x += 2;
	}
	else
	{
		mAnimation->Play(L"Stand_R");
	}
}

void GamePlayer::OnRender(Graphics* graphics)
{	
	graphics->Draw(mPosition, mAnimation->GetCurrentSprite());
}

GamePlayer::GamePlayer(int x, int y) 
	: GameObject(x, y), mAnimation(nullptr)
{	
}