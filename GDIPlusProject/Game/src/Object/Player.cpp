#include "Object/Player.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "Manager/ScoreManager.h"

Player::~Player()
{
}

void Player::Initialize()
{
	// 스프라이트 데이터 생성
	spriteRenderer[0] = AddComponent<SpriteRenderer>();

	// 그외 컴포넌트 생성
	collider = AddComponent<Collider>();

	spriteRenderer[0]->GetImage(L"./Resource/Player/Idle-Sheet.png");
	spriteRenderer[0]->GetImageInfo(L"Idle", L"./Resource/Player/animSize.csv");

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;

	speed = 350.0f;

	transform->position = Vector2(200, 200);
	transform->width = 32;
	transform->height = 32;

	collider->bound = { 0, 50, 50, 0 };
	collider->UpdateValue(this);

	gravity = AddComponent<Gravity>();
}

void Player::Update()
{
	if (shouldBeDeleted) return;

	gravity->Update();

	animationGameTimer += g_GameTime.GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer[playerState]->currFrame++;
		spriteRenderer[playerState]->currFrame %= spriteRenderer[playerState]->imageFrameCount;
	}

	moveDirection = Vector2(0.0f, 0.0f);
	float jumpValue = (float)jumpPower * (float)g_GameTime.GetDeltaTime();

	if (g_Input.IsKeyDown(VK_DOWN))
	{
		moveDirection = Vector2(moveDirection.x, 1.0f);
	}
	if (g_Input.IsKeyDown(VK_UP))
	{
		//moveDirection = Vector2(moveDirection.x, -1.0f);
		OnJump(jumpValue);
	}
	if (g_Input.IsKeyDown(VK_LEFT))
	{
		moveDirection = Vector2(-1.0f, moveDirection.y);
	}

	if (g_Input.IsKeyDown(VK_RIGHT))
	{
		moveDirection = Vector2(1.0f, moveDirection.y);
	}

	transform->Translate(moveDirection.x * speed * g_GameTime.GetDeltaTime(), moveDirection.y * jumpValue);
	collider->UpdateValue(this);
	CheckJumpHeight();
}

void Player::Render()
{
	if (shouldBeDeleted) return;

	if (graphics != nullptr)
	{
		spriteRenderer[playerState]->DrawImage(graphics, (int)transform->position.x, (int)transform->position.y);
	}
}

// Event ----------------------------------------------------------------------------------------------------------------

void Player::OnColliderOverlap(GameObject* other)
{
	if (shouldBeDeleted) return;

	//other->shouldBeDeleted = true; // 닿은 오브젝트 제거
	g_ScoreManager.AddScore();
}

void Player::OnColliderExit(GameObject* other)
{
	if (shouldBeDeleted) return;
}

void Player::OnJump(float jumpValue)
{
	if (currentJumpHeight <= maxJumpHeight && canJump) // -> 누른 만큼 올라감
	{
		moveDirection = Vector2(moveDirection.x, -1.0f);
		currentJumpHeight += jumpValue;
	}
}

void Player::CheckJumpHeight()
{
	if (currentJumpHeight >= 0.0f && gravity->GetIsGround())
	{
		currentJumpHeight = 0.0f;
		canJump = true;
	}
}