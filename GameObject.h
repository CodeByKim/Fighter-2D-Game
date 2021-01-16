#pragma once

#include "Library.h"
#include "BaseObject.h"

class Sprite;

class GameObject : public BaseObject
{
public:
	GameObject(const wchar_t* spriteName);
	void				OnUpdate() override;
	void				OnRender(Graphics* graphics) override;

protected:
	Sprite*				mSprite;
	Position2D			mPosition;
};

