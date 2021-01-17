#pragma once

#include "Library.h"
#include "BaseComponent.h"

class GameObject;

class ObjectComponent : public BaseComponent
{
public:
	void Execute(std::vector<GameObject*>& gameObjects) override;	

private:
	
};