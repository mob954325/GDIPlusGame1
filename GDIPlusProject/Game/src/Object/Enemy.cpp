#include "Object/Enemy.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/Input.h"

Enemy::~Enemy()
{
	
}

void Enemy::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	collider = AddComponent<Collider>();	

	spriteRenderer->GetImage(L"./Resource/Enemy/Idle-Sheet.png");
	spriteRenderer->GetImageInfo(L"Idle", L"./Resource/Enemy/animSize.csv");

	transform->width = 28;
	transform->height = 28;

	collider->bound = { 0, (LONG)transform->height, (LONG)transform->width, 0 };
}

void Enemy::UpdateImpl()
{

}
 
void Enemy::RenderImpl()
{

}

void Enemy::OnColliderEnterImpl(GameObject* other)
{
}

void Enemy::OnColliderExitImpl(GameObject* other)
{
}