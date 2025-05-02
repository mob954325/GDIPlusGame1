#include "Object/TerrainObject.h"
TerrainObject::~TerrainObject()
{
}

void TerrainObject::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	spriteRenderer->GetImage(L"./Resource/Tile/Terrain (16x16).png");
	spriteRenderer->GetImageInfo(L"Rock1", L"./Resource/Tile/TerrainSize.csv");

	collider = AddComponent<Collider>();

	spriteRenderer->currFrame = tileNumber;
}

void TerrainObject::UpdateImpl()
{
}

void TerrainObject::RenderImpl()
{
}

void TerrainObject::SetupTransform(int gridX, int gridY)
{
	// note : tilenumber 초기화됨, 모든 데이터는 이상 없음
	//		  이미지가 안그려짐

	transform->SetTransform((float)(gridX * spriteRenderer->drawWidth), (float)(gridY * spriteRenderer->drawHeight));

	//printf("ground %d", spriteRenderer->drawWidth);

	transform->width = (float)(spriteRenderer->drawWidth);
	transform->height = (float)(spriteRenderer->drawHeight);

	//collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.x };

	//printf("%f %f\n", transform->position.x, transform->position.y);
}

void TerrainObject::OnColliderEnterImpl(GameObject* other)
{
}

void TerrainObject::OnColliderExitImpl(GameObject* other)
{
}
