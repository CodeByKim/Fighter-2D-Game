#pragma once
#include "Library.h"

class Sprite;

struct SpriteAnimationInfo
{
	int delay;
	int currentFrame;

	std::vector<Sprite*> animation;
	Sprite* currentSprite;
};

class SpriteAnimation
{
public:
	void AddAnimation(const wchar_t* fileName, GameObject* owner, int delay, DWORD colorKey = 0x00ffffff);
	void Play(std::wstring_view animationName);
	Sprite* GetCurrentSprite();

private:
	bool HasAnimation(std::wstring_view animationName);
	void NextFrame();
	void ResetFrame();

	std::unordered_map<std::wstring, SpriteAnimationInfo*> mAnimations;
	SpriteAnimationInfo* mCurrentAnimation;
	int mIndex;
};