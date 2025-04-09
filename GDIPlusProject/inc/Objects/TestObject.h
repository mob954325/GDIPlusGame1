#pragma once
#include "Manager/UtilityManager.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Objects/GameObject.h"
#include "Objects/Player.h"

class TestObject : public GameObject
{
public:
	TestObject();
	~TestObject();

	void Initialize();
	void Update();
	void Render(Gdiplus::Graphics* graphics);

	void OnColliderOverlap(SpriteCollider* other);

protected:
	SpriteRenderer* spriteRenderer;
	SpriteCollider* collider;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};