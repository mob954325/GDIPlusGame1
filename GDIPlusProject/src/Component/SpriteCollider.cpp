#include "Component/SpriteCollider.h"

void SpriteCollider::RenderCollider(Gdiplus::Graphics* graphics)
{
#if _DEBUG
	Gdiplus::Pen myPen(Gdiplus::Color(255,255,255,255), 1.0f);
	graphics->DrawRectangle(&myPen, minX, minY, maxX - minX, maxY - minY);
#endif
}

SpriteCollider::SpriteCollider()
{
	minX = 0.0f; maxX = 0.0f;
	minY = 0.0f; maxY = 0.0f;
}

SpriteCollider::~SpriteCollider()
{
}

void SpriteCollider::UpdateValue(GameObject* object, SpriteRenderer* spriteRenderer)
{
	minX = object->transform->position.x;
	maxX = minX + spriteRenderer->imageWidth;

	minY = object->transform->position.y;
	maxY = minY + spriteRenderer->imageWidth;
}

bool SpriteCollider::IsOverlap(SpriteCollider* objectA, SpriteCollider* objectB)
{
	return objectA->minX < objectB->maxX && objectA->maxX > objectB->minX &&
		   objectA->minY < objectB->maxY && objectA->maxY > objectB->minY;
}

SpriteCollider* SpriteCollider::GetColliderComponent()
{
	return this;
}
