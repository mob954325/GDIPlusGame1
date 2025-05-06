#include "Object/Spike.h"

Spike::~Spike()
{
}

void Spike::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	collider = AddComponent<Collider>();

	spriteRenderer->GetImage(L"./Resource/Enemy/Spike-Idle.png", false);
	spriteRenderer->GetImageInfo(L"Spike", L"./Resource/Enemy/animSize.csv");

	transform->width = 16;
	transform->height = 16;

	collider->bound = { 0, (LONG)transform->height, (LONG)transform->width, 0 };
}