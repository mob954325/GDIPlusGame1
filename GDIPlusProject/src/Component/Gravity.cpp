#include "Component/Gravity.h"

Gravity::Gravity()
{
	owner = nullptr;
	ownerHeight = 0;
	fallingSpeed = 550.0f;

	isGround = false;
}

Gravity::~Gravity()
{
}

void Gravity::Initialize(GameObject* objectPtr)
{
	owner = objectPtr;
	ownerHeight = owner->GetComponent<SpriteRenderer>()->imageHeight; // 임시
}

void Gravity::Update()
{
	if (owner == nullptr)
	{
		printf("owner가 존재하지 않습니다.\n");
		return;
	}

	// 임시
	if (!isGround)
	{
		owner->transform->Translate(0.0f, fallingSpeed * GameTime::GetDeltaTime());
	}
}

float Gravity::GetFallingSpeed()
{
	return fallingSpeed;
}

void Gravity::SetIsGround(bool value)
{
	isGround = value;
}

bool Gravity::GetIsGround()
{
	return isGround;
}
