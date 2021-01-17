#include "Game.h"
#include "GameObject.h"
#include "Graphics.h"
#include "ObjectComponent.h"
#include "Sprite.h"

GameObject::GameObject(int x, int y)
{	
	mIsStart = true;	
	mPosition = { x, y };
}

void GameObject::OnUpdate()
{	
	if (mIsStart)
	{
		Start();
		mIsStart = false;
	}
	else
	{
		OnFrameUpdate();
	}
}