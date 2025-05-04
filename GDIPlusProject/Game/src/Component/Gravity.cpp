#include "Component/Gravity.h"

Gravity::Gravity()
{
	owner = nullptr;
	fallingSpeed = 10.0f; // 
	isGround = false;
}

Gravity::~Gravity()
{
}

void Gravity::Initialize()
{
}

void Gravity::Update()
{

	if (owner == nullptr)
	{
		printf("owner가 존재하지 않습니다.\n");
		return;
	}
	
	ApplyGravity();
	ApplyFrictionForce();
	ClampVelocity();

	//printf("%f %f\n", velocity.x, velocity.y);
}

void Gravity::Render()
{
}

Vector2 Gravity::GetVelocity()
{
	//printf("%f %f\n", velocity.x, velocity.y);
	return velocity;
}

void Gravity::ApplyForce(Vector2 forceVec)
{
	velocity += forceVec;
}

void Gravity::SetVelocityZero()
{
	velocity = { 0,0 };
}

void Gravity::SetVelocityYZero()
{
	velocity.y = 0;
}

void Gravity::SetVelocityXZero()
{
	velocity.x = 0;
}

void Gravity::SetIsGround(bool value)
{
	isGround = value;
}

bool Gravity::GetIsGround()
{
	return isGround;
}

void Gravity::ApplyFrictionForce()
{
	if (abs((double)velocity.x) > 0)
	{
		if (velocity.x > 0.0f)
		{
			velocity.x -= frictionForce * g_GameTime.GetDeltaTime();
			if (velocity.x < 0.0f) velocity.x = 0.0f;
		}
		else if (velocity.x < 0.0f)
		{
			velocity.x += frictionForce * g_GameTime.GetDeltaTime();
			if (velocity.x > 0.0f) velocity.x = 0.0f;
		}
	}
}

void Gravity::ApplyGravity()
{
	if (!isGround)
	{
		velocity.y += fallingSpeed * g_GameTime.GetDeltaTime();
	}
	else
	{
		velocity.y = 0.0f;
	}
}

void Gravity::ClampVelocity()
{
	if (velocity.x > maxVelocityX) velocity.x = maxVelocityX;
	if (velocity.x < -maxVelocityX) velocity.x = -maxVelocityX;
	if (velocity.y > maxVelocityY) velocity.y = maxVelocityY;
	if (velocity.y < -maxVelocityY) velocity.y = -maxVelocityY;
}
