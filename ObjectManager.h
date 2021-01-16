#pragma once

#include "Library.h"
#include "GameObject.h"

class ObjectManager
{
public:
	GameObject* Get();
	void Release(GameObject* object);

private:

};