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
	//��������Ʈ ���� �ʿ�
	//��ũ�� ���� �ʿ� (Ŭ����)
	//��������Ʈ ����, ��ũ������ �ʿ�
	graphics->Draw(mPosition, mSprite);
}