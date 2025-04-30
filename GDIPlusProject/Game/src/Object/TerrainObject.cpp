#include "Object/TerrainObject.h"

TerrainObject::~TerrainObject()
{
}

void TerrainObject::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	spriteRenderer->GetImage(L"./Resource/Tile/Terrain (16x16).png");
	spriteRenderer->GetImageInfo(L"Rock2", L"./Resource/Tile/TerrainSize.csv");

	collider = AddComponent<Collider>();

	spriteRenderer->currFrame = 52;
}

void TerrainObject::UpdateImpl()
{
}

void TerrainObject::RenderImpl()
{
}

void TerrainObject::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform((float)(gridX * spriteRenderer->drawWidth), (float)(gridY * spriteRenderer->drawHeight));

	//printf("ground %d", spriteRenderer->drawWidth);

	transform->width = (float)(spriteRenderer->drawWidth * countX);
	transform->height = (float)(spriteRenderer->drawHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.x };
}

void TerrainObject::OnColliderEnterImpl(GameObject* other)
{
}

void TerrainObject::OnColliderExitImpl(GameObject* other)
{
}
