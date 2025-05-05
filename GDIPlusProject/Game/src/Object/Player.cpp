#define NOMINMAX
#include <algorithm>

#include "Object/Player.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "Manager/ScoreManager.h"

#include "Object/GroundObject.h"
#include "Object/Enemy.h"


Player::~Player()
{
}

void Player::Initialize()
{
	// 스프라이트 데이터 생성
	spriteRenderer[0] = AddComponent<SpriteRenderer>();
	spriteRenderer[0]->GetGraphic(&graphics);

	spriteRenderer[0]->GetImage(L"./Resource/Player/Idle-Sheet.png");
	spriteRenderer[0]->GetImageInfo(L"Idle", L"./Resource/Player/animSize.csv");

	// 그외 컴포넌트 생성
	collider = AddComponent<Collider>();

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;

	transform->position = Vector2(200, 200);
	transform->width = 32;
	transform->height = 32;

	collider->bound = { 0, 50, 50, 0 };

	gravity = AddComponent<Gravity>();
}

void Player::UpdateImpl()
{
	Vector2 inputForce = Vector2(0.0f, 0.0f);

	if (g_Input.IsKeyDown('W'))
	{
		transform->Translate(0.0f, -110.0f);
	}

	if (g_Input.IsKeyDown(VK_DOWN))
	{
		//moveDirection = Vector2(moveDirection.x, 1.0f);
	}
	if (g_Input.IsKeyDown(VK_UP))
	{
		OnJump();
	}
	if (g_Input.IsKeyDown(VK_LEFT) && canMoveLeft)
	{
		inputForce.x = -speed;
	}
	if (g_Input.IsKeyDown(VK_RIGHT) && canMoveRight)
	{
		inputForce.x = speed;
	}

	gravity->ApplyForce(inputForce);
	gravity->Update();	//

	canJump = gravity->GetIsGround(); // isGround로 점프 가능한지 체크

	transform->Translate(gravity->GetVelocity() * g_GameTime.GetDeltaTime());

	//printf("%s\n", gravity->GetIsGround() ? "true": "false");
	//printf("%f\n", gravity->GetVelocity().y);
	//printf("%f\n", transform->position.y);

	LimitPositionInScreen();
}

void Player::RenderImpl()
{
}

// Event ----------------------------------------------------------------------------------------------------------------

void Player::OnColliderEnterImpl(GameObject* other)
{
	//Enemy* enemy = dynamic_cast<Enemy*>(other);
	//if (enemy != nullptr)
	//{
	//	other->shouldBeDeleted = true; // 닿은 오브젝트 제거
	//	g_ScoreManager.AddScore();
	//}

	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	OnGroundColliderEnter(ground);
}

void Player::OnColliderStayImpl(GameObject* other)
{
	
}

void Player::OnColliderExitImpl(GameObject* other)
{
	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	if (ground != nullptr)
	{
		gravity->SetIsGround(false);
		canMoveLeft = true;
		canMoveRight = true;
	}
}

void Player::OnJump()
{
	if (canJump && gravity->GetIsGround()) // -> 누른 만큼 올라감
	{
		gravity->ApplyForce(Vector2(0.0f, -jumpPower));
		gravity->SetIsGround(false);
	}
}

void Player::OnGroundColliderEnter(GroundObject* ground)
{
	if (ground == nullptr || gravity->GetIsGround())
		return;

	// 플레이어 및 지형의 AABB 정보
	float playerLeft = transform->position.x;
	float playerRight = playerLeft + transform->width;
	float playerBottom = transform->position.y;
	float playerTop = playerBottom + transform->height;

	float groundLeft = ground->transform->position.x;
	float groundRight = groundLeft + ground->transform->width;
	float groundBottom = ground->transform->position.y;
	float groundTop = groundBottom + ground->transform->height;

	// 겹친 영역
	float overlapX = std::min(playerRight, groundRight) - std::max(playerLeft, groundLeft);
	float overlapY = std::min(playerTop, groundTop) - std::max(playerBottom, groundBottom);

	printf(" x : %f Y: %f\n", overlapX, overlapY);

	// 이동 속도
	Vector2 velocity = gravity->GetVelocity();

	if (std::abs(velocity.y) > std::abs(velocity.x))
	{
		if (velocity.y >= -1.0f && playerBottom < groundTop && playerTop > groundBottom)
		{
			gravity->SetIsGround(true);
			if (playerTop < groundBottom)
			{
				transform->position.y = groundBottom - transform->height;
			}

			gravity->SetVelocityYZero();
		}
		else
		{
			// 머리 충돌
			gravity->SetVelocityYZero();
		}
	}
	else
	{
		// X축 충돌 (벽)
		gravity->SetVelocityXZero();

		if (velocity.x > 0)
			canMoveRight = false;
		else if (velocity.x < 0)
			canMoveLeft = false;
	}
}

void Player::LimitPositionInScreen()
{
	if (transform->position.x < 0) transform->position.x = 0;
	if (transform->position.y + transform->height > g_WindowConfig.windowHeight) transform->position.y = g_WindowConfig.windowHeight - transform->height;
	if (transform->position.x + transform->width > g_WindowConfig.windowWidth) transform->position.x = g_WindowConfig.windowWidth - transform->width;
}