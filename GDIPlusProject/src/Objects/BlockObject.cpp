#include "Objects/BlockObject.h"

void BlockObject::Initialize()
{
	collider = AddComponent<SpriteCollider>();
}

void BlockObject::Update()
{

}

void BlockObject::Render(Gdiplus::Graphics* graphics)
{

}

void BlockObject::OnColliderOverlap(GameObject* other)
{

}

void BlockObject::OnColliderExit(GameObject* other)
{

}

void BlockObject::SpawnBlock(RECT bound, Vector2 position)
{
}
