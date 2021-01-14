#include "GameObject.h"
#include "Graphics.h"
#include "Sprite.h"

GameObject::GameObject()
{
	mSprite = Sprite::Create(L"Test.bmp", this);
	mSprite->SetPivot(71, 90);

	mPosition = { 50, 50 };
}

void GameObject::Update()
{

}