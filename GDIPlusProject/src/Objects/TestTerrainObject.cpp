#include "Objects/TestTerrainObject.h"

TestTerrainObject::TestTerrainObject()
{
	tileSprite = {};
	collider = {};
}

TestTerrainObject::~TestTerrainObject()
{
	tileSprite->DeleteImage();
}

void TestTerrainObject::Initialize()
{
	tileSprite = new SpriteRenderer();

	tileSprite->GetImage(L"./Resource/BackGround/Yellow.png");
	tileSprite->GetImageInfo(L"Yellow", L"./Resource/Background/mapSize.csv");

	AddComponet(tileSprite);

	collider = new SpriteCollider();
	int top = tileSprite->imageHeight * 8;
	int right = tileSprite->imageWidth * 10;
	int bottom = tileSprite->imageHeight * 10;

	collider->bound = { 0, tileSprite->imageHeight * 10, tileSprite->imageWidth * 10, tileSprite->imageHeight * 9 };
	//collider->bound = { 0, 20, 20, 0};
	AddComponet(collider);
}

void TestTerrainObject::Update()
{
	//collider->UpdateValue(this, tileSprite);
}

void TestTerrainObject::Render(Gdiplus::Graphics* graphics)
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (tiles[y][x] == 1)
			{
				tileSprite->DrawImage(graphics, x * tileSprite->imageWidth, y * tileSprite->imageHeight);
			}
		}
	}

	collider->RenderCollider(graphics);
}

void TestTerrainObject::OnColliderOverlap(GameObject* other)
{
	printf("테스트 지형 충돌\n");
	other->GetComponent<Gravity>()->SetIsGround(true);
}
