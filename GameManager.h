#pragma once

#include "Library.h"
#include "GameObject.h"

class GamePlayer;

class GameManager : public GameObject
{
public:
	void						OnStart() override;
	void						OnFrameUpdate() override;
	void						OnRender(Graphics* gra1phics) override;

	GameManager();

private:
	std::vector<GamePlayer*>	mPlayers;
};