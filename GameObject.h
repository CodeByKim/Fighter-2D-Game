#pragma once

#include "Library.h"
#include "BaseObject.h"

class Sprite;

class GameObject : public BaseObject
{
public:	
	void				OnUpdate() override;
	void				OnRender(Graphics* graphics) override;

						GameObject();

protected:
	Sprite*				mSprite;
	Position2D			mPosition;
};