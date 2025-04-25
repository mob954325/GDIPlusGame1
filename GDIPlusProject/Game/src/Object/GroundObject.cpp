#include "Object/GroundObject.h"
#include "Component/Gravity.h"

GroundObject::~GroundObject()
{
}

void GroundObject::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	collider = AddComponent<Collider>();

	spriteRenderer->GetImage(L"./Resource/Tile/Blue.png");
	spriteRenderer->GetImageInfo(L"Blue", L"./Resource/Tile/tileSize.csv");
}

void GroundObject::Update()
{
}

void GroundObject::Render()
{
	for (int y = 0; y < transform->height / spriteRenderer->imageHeight; y++)
	{
		for (int x = 0; x < transform->width / spriteRenderer->imageWidth; x++)
		{
			spriteRenderer->DrawImage(graphics, (int)(transform->position.x + x * spriteRenderer->imageWidth), (int)(transform->position.y + y * spriteRenderer->imageHeight));
		}
	}
}

/// NOTE
/// bound left 와 bound right 값이 잘못됨

void GroundObject::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform(gridX * spriteRenderer->imageWidth, gridY * spriteRenderer->imageHeight);

	transform->width = (float)(spriteRenderer->imageWidth * countX);
	transform->height = (float)(spriteRenderer->imageHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.y };
	collider->Update(this);
}

void GroundObject::OnColliderEnter(GameObject* other)
{
}

void GroundObject::OnColliderExit(GameObject* other)
{

}
