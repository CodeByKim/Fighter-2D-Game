#pragma once

#include "Library.h"
#include "BaseComponent.h"

//�ʿ� ���� ���� ����.. 
class CollisionComponent : public BaseComponent
{
public:
	void Execute(std::vector<GameObject*>& gameObjects) override;

private:
};
