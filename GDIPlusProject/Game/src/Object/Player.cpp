#include "Object/Player.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "Manager/ScoreManager.h"
#include "Object/GroundObject.h"

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

	transform->position = Vector2(200, 200);
	transform->width = 32;
	transform->height = 32;

	collider->bound = { 0, 50, 50, 0 };
	collider->Update(this);

	gravity = AddComponent<Gravity>();
}

void Player::Update()
{
	if (shouldBeDeleted) return;

	animationGameTimer += g_GameTime.GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer[playerState]->currFrame++;
		spriteRenderer[playerState]->currFrame %= spriteRenderer[playerState]->imageFrameCount;
	}

	Vector2 inputForce = Vector2(0.0f, 0.0f);

	if (g_Input.IsKeyDown(VK_DOWN))
	{
		//moveDirection = Vector2(moveDirection.x, 1.0f);
	}
	if (g_Input.IsKeyDown(VK_UP))
	{
		OnJump();
	}
	if (g_Input.IsKeyDown(VK_LEFT))
	{
		inputForce.x = -speed;
	}

	if (g_Input.IsKeyDown(VK_RIGHT))
	{
		inputForce.x = speed;
	}

	gravity->ApplyForce(inputForce);
	gravity->Update();	//

	canJump = gravity->GetIsGround(); // isGround로 점프 가능한지 체크

	collider->Update(this); //
	transform->Translate(gravity->GetVelocity() * g_GameTime.GetDeltaTime());

	printf("%s\n", gravity->GetIsGround() ? "true": "false");
	//printf("%f\n", transform->position.y);
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

void Player::OnColliderEnter(GameObject* other)
{
	if (shouldBeDeleted) return;

	//other->shouldBeDeleted = true; // 닿은 오브젝트 제거
	//g_ScoreManager.AddScore();

	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	if (ground != nullptr && !gravity->GetIsGround())
	{
		float playerBottom = transform->position.y + transform->height;
		float groundTop = ground->transform->position.y;

		if (gravity->GetVelocity().y >= 0.0f)
		{
			transform->position.y = groundTop - transform->height;
			gravity->SetIsGround(true);
			gravity->SetVelocityYZero();
		}
	}
}

void Player::OnColliderStay(GameObject* other)
{
}

void Player::OnColliderExit(GameObject* other)
{
	if (shouldBeDeleted) return;

	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	if (ground != nullptr) gravity->SetIsGround(false);
}

void Player::OnJump()
{
	if (canJump && gravity->GetIsGround()) // -> 누른 만큼 올라감
	{
		gravity->ApplyForce(Vector2(0.0f, -jumpPower));
		gravity->SetIsGround(false);
	}
}