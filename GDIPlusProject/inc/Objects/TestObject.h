#pragma once
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Objects/GameObject.h"
#include "Objects/Player.h"

class TestObject : public GameObject
{
public:
	TestObject();
	TestObject(int positionX, int positionY);
	~TestObject();

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	void OnColliderOverlap(SpriteCollider* other);

protected:
	SpriteRenderer* spriteRenderer;
	SpriteCollider* collider;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};