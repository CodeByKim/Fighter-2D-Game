#pragma once

class Graphics;

class IRenderable
{
public:
	virtual void OnRender(Graphics* graphic) = 0;
};