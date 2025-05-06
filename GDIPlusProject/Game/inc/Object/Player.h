#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"
#include "Component/Gravity.h"
#include "Object/GroundObject.h"

class Player : public GameObject
{
public:
	Player(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Player();
	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderStayImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;
	int GetHp();

protected:
	void OnJump();
	void OnGroundColliderEnter(GroundObject* ground);
	void LimitPositionInScreen();
	void UpdateTimer();
	void UpdateAnimation();
	void SetAnimation(int index);
	void ShowPlayerHealthUI();

	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer[4];
	Collider* collider = nullptr;
	Gravity* gravity = nullptr;
	Vector2 moveDirection = Vector2(0.0f, 0.0f);

	// state
	int hp = 5;
	int playerState = 0;
	float speed = 220.0f;		 // 플레이어 이동 속도
	float jumpPower = 600.0f;

	bool canJump = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	// time
	float hitDelayTimer = 0.0f;
	float maxHitDelayTime = 2.0f;
};

