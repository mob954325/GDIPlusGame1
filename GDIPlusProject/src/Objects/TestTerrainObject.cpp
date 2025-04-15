#include "Objects/TestTerrainObject.h"

TestTerrainObject::TestTerrainObject()
{
	tileSprite = {};
	collider = {};
	collider2 = {};
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
	collider2 = new SpriteCollider();

	// 임시
	int top = tileSprite->imageHeight * 8;
	int right = tileSprite->imageWidth * 10;
	int bottom = tileSprite->imageHeight * 10;

	collider->bound = { 0, tileSprite->imageHeight * 10, tileSprite->imageWidth * 10, tileSprite->imageHeight * 9 };
	collider2->bound = { 0, tileSprite->imageHeight * 8, tileSprite->imageWidth * 6, tileSprite->imageHeight * 7 };
	//collider->bound = { 0, 20, 20, 0};
	AddComponet(collider);
	AddComponet(collider2);
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
	collider2->RenderCollider(graphics);
}

void TestTerrainObject::OnColliderOverlap(GameObject* other)
{
	Gravity* comp = other->GetComponent<Gravity>();
	if (comp != nullptr)
	{
		comp->SetIsGround(true);
	}
}

void TestTerrainObject::OnColliderExit(GameObject* other)
{
	Gravity* comp = other->GetComponent<Gravity>();
	if (comp != nullptr)
	{
		other->GetComponent<Gravity>()->SetIsGround(false);
	}
}

void TestTerrainObject::SetCollider()
{
}
