#pragma once

#include "Library.h"
#include "BaseObject.h"
#include "IRenderable.h"

class Sprite;

class GameObject : public BaseObject
{
public:
	GameObject();
	void				Update() override;	

protected:
	Sprite*				mSprite;
	Position2D			mPosition;
};

