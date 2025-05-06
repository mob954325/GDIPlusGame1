#include "Object/Enemy.h"
#include "Object/GroundObject.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"

Enemy::~Enemy()
{
	
}

void Enemy::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	collider = AddComponent<Collider>();	

	spriteRenderer->GetImage(L"./Resource/Enemy/Enemy-Idle.png", false);
	spriteRenderer->GetImageInfo(L"Enemy", L"./Resource/Enemy/animSize.csv");

	transform->width = 28;
	transform->height = 28;

	collider->bound = { 0, (LONG)transform->height, (LONG)transform->width, 0 };
}

void Enemy::UpdateImpl()
{
	transform->Translate(moveDirection.x * speed * g_GameTime.GetDeltaTime(), 0.0f);
	LimitPositionInScreen();
}
 
void Enemy::RenderImpl()
{

}

void Enemy::OnColliderEnterImpl(GameObject* other)
{
	GroundObject* ground = dynamic_cast<GroundObject*>(other);
	if (ground == nullptr) return;

	if (ground->transform->position.y >= transform->position.y + transform->height) return;

	float deltaX = transform->position.x - ground->transform->position.x;

	if (deltaX < 0)
	{
		// 적이 벽의 왼쪽에서 충돌
		moveDirection.x = -1;
		transform->position.x -= 20.0f; // 왼쪽에서 밀려나기
	}
	else
	{
		// 적이 벽의 오른쪽에서 충돌
		moveDirection.x = 1;
		transform->position.x += 20.0f; // 오른쪽에서 밀려나기
	}
}

void Enemy::OnColliderExitImpl(GameObject* other)
{
}

void Enemy::LimitPositionInScreen()
{
	if (transform->position.x < 0)
	{
		transform->position.x = 0;
		moveDirection.x = 1;
	}
	if (transform->position.x + transform->width > g_WindowConfig.windowWidth)
	{
		transform->position.x = g_WindowConfig.windowWidth - transform->width;
		moveDirection.x = -1;
	}
	if (transform->position.y + transform->height > g_WindowConfig.windowHeight) transform->position.y = g_WindowConfig.windowHeight - transform->height;
}