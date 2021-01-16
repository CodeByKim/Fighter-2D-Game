#include "ObjectComponent.h"
#include "GameObject.h"

void ObjectComponent::Execute(std::vector<GameObject*>& gameObjects)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->OnUpdate();
	}
}