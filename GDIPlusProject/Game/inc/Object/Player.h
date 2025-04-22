#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"
#include "Component/Gravity.h"

class Player : public GameObject
{
public:
	Player(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Player();
	void Initialize() override;
	void Update() override;
	void Render() override;

	// Event
	void OnColliderOverlap(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;

protected:
	void OnJump();

	Gdiplus::Graphics* graphics = {};
	SpriteRenderer* spriteRenderer[1];
	Collider* collider = {};
	Gravity* gravity = {};
	Vector2 moveDirection = {};

	// state
	int playerState = 0;
	float speed = 220.0f;		 // 플레이어 이동 속도
	float jumpPower = 600.0f;

	bool canJump = true;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};

