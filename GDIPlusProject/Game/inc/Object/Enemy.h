#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/Collider.h"
#include "Component/SpriteRenderer.h"

class Enemy : public GameObject
{
public:
	Enemy(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Render() override;

	// Event
	void OnColliderOverlap(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;

protected:
	Gdiplus::Graphics* graphics = {};
	SpriteRenderer* spriteRenderer;
	Collider* collider = nullptr;
	Vector2 moveDirection = {};

	float speed = 0;

	float animationGameTimer;
	float maxAnimationGameTime;
};

