#include "TerrainObject.h"

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
}

void TerrainObject::UpdateImpl()
{
}

void TerrainObject::RenderImpl()
{
	for (int y = 0; y < transform->height / spriteRenderer->drawHeight; y++)
	{
		for (int x = 0; x < transform->height / spriteRenderer->drawHeight; x++)
		{
			spriteRenderer->DrawImage(y, x, 50); // 랜더 중복 출력으로 그림 안보임
		}
	}
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
