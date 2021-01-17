#pragma once

#include "Library.h"
#include "BaseObject.h"

class Sprite;

class GameObject : public BaseObject
{
public:		
	void				OnUpdate() override;
	virtual void		OnFrameUpdate() = 0;

	GameObject(int x, int y);

protected:	
	Position2D			mPosition;	

private:
	bool				mIsStart;
};