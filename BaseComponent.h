#pragma once

#include "Library.h"
class GameObject;

class BaseComponent
{
public:
	virtual void			Execute(std::vector<GameObject*>& gameObjects) = 0;
	std::wstring_view		GetName();

protected:
	std::wstring			mName;
};

