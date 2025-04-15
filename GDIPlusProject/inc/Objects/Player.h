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

	void OnColliderOverlap(GameObject* other) override;

protected:
	SpriteRenderer* spriteRenderer[3]; // 임시 개수 선언
	SpriteCollider* collider;
	Gravity* gravity;
	Vector2 moveDirection;

	// state
	int playerState = 0; // idle, turn, hurt
	float speed;				// 플레이어 이동 속도
	float jumpForce;			// 점프 시 올라갈 때 받을 값
	float maxJumpHeight;		// 플레이어 최대 점프 높이
	float currentJumpHeight;	// 플레이어 현재 점프 높이
	bool canJump = false;		// 점프 가능 여부

	// time
	float animationGameTimer;
	float maxAnimationGameTime;

private:
	// 땅에 닿았을 때 올라간 점프높이를 초기화하는 함수
	void CheckJumpHeight();
	void PlayerJump(float jumpValue);
};

/// 조작 
/// VK_DOWN  - 없음
/// VK_UP	 - 점프
/// VK_LEFT  - 왼쪽 이동
/// VK_RIGHT - 오른쪽이동