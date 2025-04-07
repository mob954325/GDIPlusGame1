#include "Objects/Player.h"

void Player::Initialize()
{
	SetDefault();

	spriteRenderer[0].GetImage(L"./Resource/Idle_Sheet.png");
	spriteRenderer[1].GetImage(L"./Resource/run_turnaround_Sheet.png");
	spriteRenderer[2].GetImage(L"./Resource/Hurt_Sheet.png");

	spriteRenderer[0].GetImageInfo(L"Idle", L"./Resource/animSize.csv");
	spriteRenderer[1].GetImageInfo(L"Turn", L"./Resource/animSize.csv");
	spriteRenderer[2].GetImageInfo(L"Hit", L"./Resource/animSize.csv");

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.04f;

	// 안내 로그
	printf("플레이어 상태 변경 : 스페이스바\n");
	printf("플레이어 움직임 : 화살표 방향키\n");
}

void Player::Update()
{
	int imageCount = 3;
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
			printf("플레이어 회전\n");
			break;
		case 1:
			printf("플레이어 대기\n");
			break;
		case 2:
			printf("플레이어 피격\n");
			break;
		default:
			break;
		}
	}

	if (Input::IsKeyDown(VK_DOWN))
	{
		transform.Translate(0.0f, 50.0f * GameTime::GetDeltaTime());
		printf("%.2f, %.2f\n", transform.x, transform.y);
		printf("down\n");
	}
	if (Input::IsKeyDown(VK_UP))
	{
		transform.Translate(0.0f, -20.0f * GameTime::GetDeltaTime());
		printf("%.2f, %.2f\n", transform.x, transform.y);
		printf("up\n");
	}
	if (Input::IsKeyDown(VK_LEFT))
	{
		transform.Translate(-20.0f * GameTime::GetDeltaTime(), 0.0f);
		printf("%.2f, %.2f\n", transform.x, transform.y);
		printf("left\n");
	}
	if (Input::IsKeyDown(VK_RIGHT))
	{
		transform.Translate(20.0f * GameTime::GetDeltaTime(), 0.0f);
		printf("%.2f, %.2f\n", transform.x, transform.y);
		printf("right\n");
	}
}

void Player::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer[playerState].DrawImage(graphics, transform.x, transform.y);
}

void Player::Uninitialize()
{
	spriteRenderer[0].DeleteImage();
	spriteRenderer[1].DeleteImage();
	spriteRenderer[2].DeleteImage();
}
