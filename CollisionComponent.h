#pragma once

#include "Library.h"
#include "BaseComponent.h"

//필요 없을 수도 있음.. 
class CollisionComponent : public BaseComponent
{
public:
	void Execute(std::vector<GameObject*>& gameObjects) override;

private:
};

