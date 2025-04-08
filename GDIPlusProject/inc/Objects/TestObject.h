#pragma once
#include "Component/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Objects/Player.h"

#include "GameTime.h"

class TestObject : GameObject
{
public:
	TestObject();

	void Initialize();
	void Update();
	void Render(Gdiplus::Graphics* graphics);
	void Uninitialize();

	void GetTargetCollider(SpriteCollider* targetCollider);

protected:
	SpriteRenderer spriteRenderer;
	SpriteCollider collider;
	SpriteCollider* target;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};