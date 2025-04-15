#include "Objects/Player.h"

Player::Player()
{
	moveDirection = Vector2(0.0f, 0.0f);

	speed = 0.0f;
	jumpForce = 0.0f;
	maxJumpHeight = 0.0f;
	currentJumpHeight = 0.0f;

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.0f;

	// 스프라이트 데이터 생성
	for (int i = 0; i < 3; i++)
	{
		spriteRenderer[i] = AddComponent<SpriteRenderer>();
	}

	// 그외 컴포넌트 생성
	collider = AddComponent<SpriteCollider>();
	gravity = AddComponent<Gravity>();
}

Player::~Player()
{
	spriteRenderer[0]->DeleteImage();
	spriteRenderer[1]->DeleteImage();
	spriteRenderer[2]->DeleteImage();
	printf("Player 소멸자 호출"); // 임시
}

void Player::Initialize()
{
	SetDefault();

	spriteRenderer[0]->GetImage(L"./Resource/Player/Idle/Idle-Sheet.png");
	spriteRenderer[1]->GetImage(L"./Resource/Player/Run/Run-Sheet.png");
	spriteRenderer[2]->GetImage(L"./Resource/Player/Jump/Jump.png");

	spriteRenderer[0]->GetImageInfo(L"Idle", L"./Resource/Player/animSize.csv");
	spriteRenderer[1]->GetImageInfo(L"Run", L"./Resource/Player/animSize.csv");
	spriteRenderer[2]->GetImageInfo(L"Jump", L"./Resource/Player/animSize.csv");

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;

	speed = 350.0f;
	maxJumpHeight = 250.0f;
	jumpForce = 2500.0f;

	gravity->Initialize(this);

	// 안내 로그
	printf("플레이어 상태 변경 : 스페이스바\n");
	printf("플레이어 움직임 : 화살표 방향키\n");
}

void Player::Update()
{
	gravity->Update();

	animationGameTimer += GameTime::GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer[playerState]->currFrame++;
		spriteRenderer[playerState]->currFrame %= spriteRenderer[playerState]->imageFrameCount;
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
		//moveDirection = Vector2(moveDirection.x, 1.0f);
	}
	if (Input::IsKeyDown(VK_UP))
	{
		//moveDirection = Vector2(moveDirection.y, -1.0f); // 디버그용 움직임
		PlayerJump();
	}
	if (Input::IsKeyDown(VK_LEFT))
	{
		moveDirection = Vector2(-1.0f, moveDirection.y);
	}
	if (Input::IsKeyDown(VK_RIGHT))
	{
		moveDirection = Vector2(1.0f, moveDirection.y);
	}

	transform->Translate(moveDirection * speed * GameTime::GetDeltaTime());
	collider->UpdateValue(this, spriteRenderer[0]);
	CheckJumpHeight();
}

void Player::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer[playerState]->DrawImage(graphics, (int)transform->position.x, (int)transform->position.y);
	collider->RenderCollider(graphics);
}

// Event ----------------------------------------------------------------------------------------------------------------

void Player::OnColliderOverlap(GameObject* other)
{
	// 충돌 내용
}

// Jump ----------------------------------------------------------------------------------------------------------------

void Player::CheckJumpHeight()
{
	// jumpHeight reset
	if (currentJumpHeight > 0.0f && gravity->GetIsGround())
	{
		currentJumpHeight = 0.0f;
	}
}

void Player::PlayerJump()
{
	double jumpValue = (double)jumpForce * (double)GameTime::GetDeltaTime();

	if (currentJumpHeight <= maxJumpHeight) // -> 누른 만큼 올라감
	{
		transform->Translate(0.0f, -jumpValue); // 점프
		currentJumpHeight += jumpValue;
		printf("current jump height %f\n", currentJumpHeight);
	}

}

// 점프 시작
// isGround-> false;
// 점프 높이 증가
// 키를 땜-> isjump = true;
// 중력 적용
// 땅에 닿음 isGround -> true