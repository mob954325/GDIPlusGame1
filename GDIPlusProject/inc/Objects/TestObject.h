#pragma once
#include "Component/GameObject.h"
#include "Component/SpriteRenderer.h"

#include "GameTime.h"

class TestObject : GameObject
{
public:
	TestObject();

	void Initialize();
	void Update();
	void Render(Gdiplus::Graphics* graphics);
	void Uninitialize();

protected:
	SpriteRenderer spriteRenderer;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};