#pragma once

#include "Library.h"
#include "BaseComponent.h"

class InputComponent : public BaseComponent
{
public:
	void Execute(std::vector<GameObject*>& gameObjects) override;

private:

};

