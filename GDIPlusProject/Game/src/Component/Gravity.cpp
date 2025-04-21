#include "Component/Gravity.h"

Gravity::Gravity()
{
	owner = nullptr;
	fallingSpeed = 550.0f;

	isGround = false;
}

Gravity::~Gravity()
{
}

void Gravity::Initialize(GameObject* objectPtr)
{
	owner = objectPtr;
}

void Gravity::Update()
{
	if (owner == nullptr)
	{
		printf("owner가 존재하지 않습니다.\n");
		return;
	}

	if (!isGround)
	{
		owner->transform->Translate(0.0f, fallingSpeed * g_GameTime.GetDeltaTime());
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

