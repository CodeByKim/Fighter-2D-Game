#pragma once

#include "Library.h"

class Graphics;

class BaseObject
{
public:
	virtual void			OnStart() = 0;
	virtual void			OnUpdate() = 0;
	virtual void			OnRender(Graphics* graphics) = 0;	
	
protected:
	std::wstring			mName;
	int						mId;
};