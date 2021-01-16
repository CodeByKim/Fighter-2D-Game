#include "GameObject.h"
#include "Graphics.h"
#include "Sprite.h"

GameObject::GameObject()
{
	mSprite = Sprite::Create(L"Attack1_R", this);

	mSprite->SetPivot(71, 90);
	mPosition = { 200, 200 };
}

void GameObject::OnUpdate()
{	
	
}

void GameObject::OnRender(Graphics* graphics)
{	
	graphics->Draw(mPosition, mSprite);
}