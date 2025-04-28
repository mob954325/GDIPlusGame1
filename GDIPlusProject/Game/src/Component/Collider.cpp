#include "Component/Collider.h"

Collider::Collider()
{
	bound = {};
}

Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
	bound.left = (LONG)owner->transform->position.x;
	bound.right = (LONG)(owner->transform->position.x + owner->transform->width);

	bound.bottom = (LONG)owner->transform->position.y;
	bound.top = (LONG)(owner->transform->position.y + owner->transform->height);
}

void Collider::Render()
{
}

bool Collider::IsOverlap(Collider* objectA, Collider* objectB)
{
	return objectA->bound.left <= objectB->bound.right && objectA->bound.right >= objectB->bound.left &&
		objectA->bound.bottom <= objectB->bound.top && objectA->bound.top >= objectB->bound.bottom;
}