#pragma once

#include "Library.h"
#include "GameObject.h"

//class Sprite;
class SpriteAnimation;
class Graphics;

class GamePlayer : public GameObject
{
public:
	void				OnStart() override;
	void				OnFrameUpdate() override;
	void				OnRender(Graphics* gra1phics) override;

	GamePlayer(int x, int y);

private:
	//Sprite* mSprite;
	SpriteAnimation* mAnimation;
};