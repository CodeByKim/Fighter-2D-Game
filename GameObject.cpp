#include "GameObject.h"
#include "Graphics.h"
#include "Sprite.h"
#include <cassert>

GameObject::GameObject(const wchar_t* spriteName)
{
	mSprite = Sprite::Create(spriteName, this);
	if (mSprite == nullptr)
	{
		assert(mSprite == nullptr);
		return;
	}

	mSprite->SetPivot(71, 90);
	mPosition = { 100, 100 };

	//mSprite->SetPivot(0, 0);
	//mPosition = { 0, 0 }; 
}

void GameObject::OnUpdate()
{	
	//OutputDebugString(L"OnUpdate\n");
}

void GameObject::OnRender(Graphics* graphics)
{
	//스프라이트 정보 필요
	//스크린 정보 필요 (클리핑)
	//스프라이트 버퍼, 스크린버퍼 필요
	graphics->Draw(mPosition, mSprite);
}