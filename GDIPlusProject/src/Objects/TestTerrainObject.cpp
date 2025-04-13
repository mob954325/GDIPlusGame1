#include "Objects/TestTerrainObject.h"

TestTerrainObject::TestTerrainObject()
{
	tileSprite = {};
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
}

void TestTerrainObject::Update()
{
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
}