#pragma once
#include "Component/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"

#include "Input.h"
#pragma comment(lib, "./lib/Input.lib")

#include "../../inc/GameTime.h"
#pragma comment(lib, "./lib/GameTime.lib")

class Player : GameObject
{
public:
	Player();
	void Initialize();
	void Update();
	void Render(Gdiplus::Graphics* graphics);
	void Uninitialize();

	SpriteCollider* r_collider; // 임시

protected:
	SpriteRenderer spriteRenderer[3]; // 임시 개수 선언
	SpriteCollider collider;
	Vector2 moveDirection;

	// state
	int playerState = 0; // idle, turn, hurt
	float Speed;

	// time
	float animationGameTimer;
	float maxAnimationGameTime;
};