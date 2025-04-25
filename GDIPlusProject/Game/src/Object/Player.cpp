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

	collider->Update(this); //
	transform->Translate(gravity->GetVelocity() * g_GameTime.GetDeltaTime());

	//printf("%s\n", gravity->GetIsGround() ? "true": "false");
	//printf("%f\n", transform->position.y);

	LimitPositionInScreen();
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
	if (ground != nullptr && !gravity->GetIsGround())
	{
		if (!gravity->GetIsGround())
		{
			Vector2 velocity = gravity->GetVelocity();

			float playerBottom = transform->position.y;
			float playerTop = playerBottom + transform->height;
			float groundBottom = ground->transform->position.y;
			float groundTop = groundBottom + ground->transform->height;


			// 랜딩 조건
			// velocity.y > 0.0f -> 떨어질 때
			// playerTop 이 groundBottom보다 낮을때 -> 플레이어가 더 위에 있을 때
			// playerBottom 이 groundBottom보다 낮을 때 -> 위와 동일

			float landingMargin = 5.0f;
			if (velocity.y > 0.0f && playerTop - landingMargin < groundBottom && playerBottom + landingMargin < groundBottom)
			{
				gravity->SetIsGround(true);
			}
			else
			{
				gravity->SetVelocityZero();

				if (velocity.x > 0)
				{
					canMoveRight = false;
				}
				else if (velocity.x < 0)
				{
					canMoveLeft = false;
				}
			}
		}
	}
}

void Player::LimitPositionInScreen()
{
	if (transform->position.x < 0) transform->position.x = 0;
	if (transform->position.y + transform->height > g_WindowConfig.windowHeight) transform->position.y = g_WindowConfig.windowHeight - transform->height;
	if (transform->position.x + transform->width > g_WindowConfig.windowWidth) transform->position.x = g_WindowConfig.windowWidth - transform->width;
}