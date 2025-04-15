#include "Component/SpriteCollider.h"

void SpriteCollider::RenderCollider(Gdiplus::Graphics* graphics)
{
#if _DEBUG
	Gdiplus::Pen myPen(Gdiplus::Color(255,255,0,0), 1.0f);
	graphics->DrawRectangle(&myPen, bound.left, (INT)bound.bottom, (INT)bound.right - (INT)bound.left, (INT)bound.top - (INT)bound.bottom);
#endif
}

SpriteCollider::SpriteCollider()
{
	bound = {};
}

SpriteCollider::~SpriteCollider()
{
}

void SpriteCollider::UpdateValue(GameObject* object, SpriteRenderer* spriteRenderer)
{
	bound.left = object->transform->position.x;
	bound.right = bound.left + spriteRenderer->imageWidth;

	bound.bottom = object->transform->position.y;
	bound.top = bound.bottom + spriteRenderer->imageWidth;
}

bool SpriteCollider::IsOverlap(SpriteCollider* objectA, SpriteCollider* objectB)
{	
	return objectA->bound.left < objectB->bound.right && objectA->bound.right > objectB->bound.left &&
		   objectA->bound.bottom < objectB->bound.top && objectA->bound.top > objectB->bound.bottom;
}