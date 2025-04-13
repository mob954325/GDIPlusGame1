#include "Objects/BackGroundObject.h"

BackGroundObject::BackGroundObject()
{
	spriteRenderer = {};

	widthCount = 0;
	heightCount = 0;
}

BackGroundObject::~BackGroundObject()
{
	spriteRenderer->DeleteImage();
}

void BackGroundObject::Initialize()
{
	spriteRenderer = new SpriteRenderer();

	spriteRenderer->GetImage(L"./Resource/BackGround/Blue.png");
	spriteRenderer->GetImageInfo(L"Blue", L"./Resource/BackGround/mapSize.csv");

	AddComponet(spriteRenderer);

	int imageWidth = spriteRenderer->imageWidth;
	int imageHeight = spriteRenderer->imageHeight;
	widthCount = g_screenWidth / imageWidth;
	heightCount = g_screenHeight / imageHeight;
}

void BackGroundObject::Update()
{
	// 사용 안함
}

void BackGroundObject::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer->DrawImage(graphics, 0, 0);
}
