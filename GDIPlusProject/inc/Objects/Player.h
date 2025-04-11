#pragma once
#include "Objects/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Component/Gravity.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

protected:
	SpriteRenderer* spriteRenderer[3]; // 임시 개수 선언
	SpriteCollider* collider;
	Gravity* gravity;
	Vector2 moveDirection;

	// state
	int playerState = 0; // idle, turn, hurt
	float speed;
	float maxJumpHeight;
	float currentJumpHeight;
	float jumpForce;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};