#define NOMINMAX
#include <algorithm>

#include "Object/Player.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "Manager/ScoreManager.h"
#include "Manager/GameManager.h"
#include "Manager/TextManager.h"
#include "Manager/SoundManager.h"

#include "Object/GroundObject.h"
#include "Object/Enemy.h"
#include "Object/Spike.h"

Player::~Player()
{
}

void Player::Initialize()
{
	// 스프라이트 데이터 생성
	spriteRenderer[0] = AddComponent<SpriteRenderer>();
	spriteRenderer[0]->GetGraphic(&graphics);

	spriteRenderer[0]->GetImage(L"./Resource/Player/Idle-Sheet.png", false);
	spriteRenderer[0]->GetImageInfo(L"Idle", L"./Resource/Player/animSize.csv");

	spriteRenderer[1] = AddComponent<SpriteRenderer>();
	spriteRenderer[1]->GetGraphic(&graphics);
	spriteRenderer[1]->GetImage(L"./Resource/Player/Idle-Sheet.png", true);
	spriteRenderer[1]->GetImageInfo(L"Hit", L"./Resource/Player/animSize.csv");
	spriteRenderer[1]->SetActive(false);

	spriteRenderer[2] = AddComponent<SpriteRenderer>();
	spriteRenderer[2]->GetGraphic(&graphics);
	spriteRenderer[2]->GetImage(L"./Resource/Player/Hit-Sheet.png", false);
	spriteRenderer[2]->GetImageInfo(L"Hit", L"./Resource/Player/animSize.csv");
	spriteRenderer[2]->SetActive(false);

	spriteRenderer[3] = AddComponent<SpriteRenderer>();
	spriteRenderer[3]->GetGraphic(&graphics);
	spriteRenderer[3]->GetImage(L"./Resource/Player/Hit-Sheet.png", true);
	spriteRenderer[3]->GetImageInfo(L"Hit", L"./Resource/Player/animSize.csv");
	spriteRenderer[3]->SetActive(false);

	// 그외 컴포넌트 생성
	collider = AddComponent<Collider>();

	transform->width = 32;
	transform->height = 32;

	collider->bound = { 0, 50, 50, 0 };

	gravity = AddComponent<Gravity>();
}

void Player::UpdateImpl()
{
	Vector2 inputForce = Vector2(0.0f, 0.0f);

#if _DEBUG
	if (g_Input.IsKeyDown('W'))
	{
		transform->Translate(0.0f, -110.0f);
	}
#endif

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
		if (!spriteRenderer[2]->GetIsActive() && !spriteRenderer[3]->GetIsActive())
		{
			SetAnimation(1);
		}
	}
	if (g_Input.IsKeyDown(VK_RIGHT) && canMoveRight)
	{
		inputForce.x = speed;
		if (!spriteRenderer[2]->GetIsActive() && !spriteRenderer[3]->GetIsActive())
		{
			SetAnimation(0);
		}
	}

	gravity->ApplyForce(inputForce);
	gravity->Update();

	canJump = gravity->GetIsGround(); // isGround로 점프 가능한지 체크

	transform->Translate(gravity->GetVelocity() * g_GameTime.GetDeltaTime());

	//printf("%s\n", gravity->GetIsGround() ? "true": "false");
	//printf("%f\n", gravity->GetVelocity().y);
	//printf("%f\n", transform->position.y);

	LimitPositionInScreen();
	UpdateAnimation();
	UpdateTimer();
}

void Player::RenderImpl()
{

#if _DEBUG
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0), 1.0f); // 빨간색, 두께 1
	graphics->DrawRectangle(
		&pen,
		(INT)(collider->bound.left),
		(INT)(collider->bound.bottom),
		(INT)(collider->bound.right - collider->bound.left),
		(INT)(collider->bound.top - collider->bound.bottom)
	);
#endif

	ShowPlayerHealthUI();
}

// Event ----------------------------------------------------------------------------------------------------------------

void Player::OnColliderEnterImpl(GameObject* other)
{
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	Spike* spike = dynamic_cast<Spike*>(other);

	// 피격
	if (enemy != nullptr || spike != nullptr)
	{
		if (hitDelayTimer > 0.0f) return;

		hp--;
		hitDelayTimer = maxHitDelayTime;
		if (moveDirection.x > 0)
		{
			SetAnimation(2);
		}
		else
		{
			SetAnimation(3);
		}

		if (hp <= 0)
		{
			// 사망
			g_GameManager.gameState = GameState::End;
		}
	}

	// 지형
	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	OnGroundColliderEnter(ground);
}

void Player::OnColliderStayImpl(GameObject* other)
{
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	Spike* spike = dynamic_cast<Spike*>(other);

	// 피격
	if (enemy != nullptr || spike != nullptr)
	{
		if (hitDelayTimer > 0.0f) return;

		hp--;
		hitDelayTimer = maxHitDelayTime;
		if (moveDirection.x > 0)
		{
			SetAnimation(2);
		}
		else
		{
			SetAnimation(3);
		}

		if (hp <= 0)
		{
			// 사망
			g_GameManager.gameState = GameState::End;
		}
	}

	// 지형
	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	if (ground != nullptr)
	{
		transform->SetTransform(transform->position);
	}
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

int Player::GetHp()
{
	return hp;
}

void Player::OnJump()
{
	if (canJump && gravity->GetIsGround())
	{
		gravity->ApplyForce(Vector2(0.0f, -jumpPower));
		gravity->SetIsGround(false);
		g_SoundManager.PlayEffectSound("./Resource/Sound/Jump.wav");
	}
}

void Player::OnGroundColliderEnter(GroundObject* ground)
{
	if (ground == nullptr || gravity->GetIsGround())
		return;

	Vector2 velocity = gravity->GetVelocity();
	float playerBottom = transform->position.y;
	float playerTop = playerBottom + transform->height;
	float groundBottom = ground->transform->position.y;
	float groundTop = groundBottom + ground->transform->height;
	
	//랜딩 조건
	//velocity.y > 0.0f -> 떨어질 때
	//playerTop 이 groundBottom보다 낮을때 -> 플레이어가 더 위에 있을 때
	//playerBottom 이 groundBottom보다 낮을 때 -> 위와 동일
	
	float landingMargin = 5.0f;
	if (velocity.y > 0.0f && playerTop + landingMargin > groundBottom && playerBottom - landingMargin < groundBottom)
	{
		gravity->SetIsGround(true);
		transform->SetTransform(transform->position.x, groundBottom - transform->height);
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

void Player::LimitPositionInScreen()
{
	if (transform->position.x < 0) transform->position.x = 0;
	if (transform->position.y + transform->height > g_WindowConfig.windowHeight) transform->position.y = g_WindowConfig.windowHeight - transform->height;
	if (transform->position.x + transform->width > g_WindowConfig.windowWidth) transform->position.x = g_WindowConfig.windowWidth - transform->width;
}

void Player::UpdateTimer()
{
	if (hitDelayTimer > 0.0f)
	{
		hitDelayTimer -= g_GameTime.GetDeltaTime();
	}
}

void Player::UpdateAnimation()
{
	if (spriteRenderer[2]->GetIsActive() || spriteRenderer[3]->GetIsActive())
	{
		if (spriteRenderer[2]->currFrame == spriteRenderer[2]->imageFrameCount - 1 ||
			spriteRenderer[3]->currFrame == spriteRenderer[3]->imageFrameCount - 1)
		{
			if (moveDirection.x > 0)
			{
				SetAnimation(0);
			}
			else
			{
				SetAnimation(1);
			}
		}
	}
}

void Player::SetAnimation(int index)
{
	if (index >= 4) return;

	for (int i = 0; i < 4; i++)
	{
		if (i == index)
		{
			spriteRenderer[i]->SetActive(true);
		}
		else
		{
			spriteRenderer[i]->SetActive(false);
		}
	}
}

void Player::ShowPlayerHealthUI()
{
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0)); // 완전한 검정색
	graphics->FillRectangle(&blackBrush, (INT)(0), (INT)(0), 100, 50);
	g_TextManager.DrawTextByViewport(L"Hp : " + std::to_wstring(hp), 0.03f, 0.0f, Gdiplus::Color::Red);
}