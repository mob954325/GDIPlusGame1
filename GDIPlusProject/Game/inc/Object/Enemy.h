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
	void UpdateImpl() override;
	void RenderImpl() override;

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer;
	Collider* collider = nullptr;
	Vector2 moveDirection = Vector2(0.0f, 0.0f);

	float speed = 0;
};

