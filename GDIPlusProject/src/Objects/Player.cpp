#include "Objects/Player.h"

Player::Player()
{
	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.0f;
	Speed = 0.0f;
	moveDirection = Vector2(0.0f, 0.0f);

	// 임시
	for (int i = 0; i < 3; i++)
	{
		spriteRenderer[i] = SpriteRenderer();
	}

	collider = SpriteCollider();
	r_collider = &collider;
}

void Player::Initialize()
{
	SetDefault();

	spriteRenderer[0].GetImage(L"./Resource/Player/Idle/Idle-Sheet.png");
	spriteRenderer[1].GetImage(L"./Resource/Player/Run/Run-Sheet.png");
	spriteRenderer[2].GetImage(L"./Resource/Player/Attack/Attack-Sheet.png");

	spriteRenderer[0].GetImageInfo(L"Idle", L"./Resource/Player/animSize.csv");
	spriteRenderer[1].GetImageInfo(L"Run", L"./Resource/Player/animSize.csv");
	spriteRenderer[2].GetImageInfo(L"Attack", L"./Resource/Player/animSize.csv");

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;

	Speed = 50.0f;

	// 안내 로그
	printf("플레이어 상태 변경 : 스페이스바\n");
	printf("플레이어 움직임 : 화살표 방향키\n");
}

void Player::Update()
{
	animationGameTimer += GameTime::GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer[playerState].currFrame++;
		spriteRenderer[playerState].currFrame %= spriteRenderer[playerState].imageFrameCount;
	}

	if (Input::IsKeyPressed(VK_SPACE))
	{
		playerState++;
		playerState %= 3;

		switch (playerState)
		{
		case 0:
			printf("플레이어 대기\n");
			break;
		case 1:
			printf("플레이어 달리기\n");
			break;
		case 2:
			printf("플레이어 공격\n");
			break;
		default:
			break;
		}

	}

	moveDirection = Vector2(0.0f, 0.0f);
	if (Input::IsKeyDown(VK_DOWN))
	{
		moveDirection = Vector2(moveDirection.x, 1.0f);
	}
	if (Input::IsKeyDown(VK_UP))
	{
		moveDirection = Vector2(moveDirection.x, -1.0f);
	}
	if (Input::IsKeyDown(VK_LEFT))
	{
		moveDirection = Vector2(-1.0f, moveDirection.y);
	}
	if (Input::IsKeyDown(VK_RIGHT))
	{
		moveDirection = Vector2(1.0f, moveDirection.y);
	}

	transform.Translate(moveDirection * Speed * GameTime::GetDeltaTime());

	collider.UpdateValue(*this, spriteRenderer[0]);
}

void Player::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer[playerState].DrawImage(graphics, transform.position.x, transform.position.y);
	collider.RenderCollider(graphics);
}

void Player::Uninitialize()
{
	spriteRenderer[0].DeleteImage();
	spriteRenderer[1].DeleteImage();
	spriteRenderer[2].DeleteImage();
}
