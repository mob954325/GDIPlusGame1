#include "Object/EndBackgroundImage.h"

EndBackgroundImage::~EndBackgroundImage()
{
}

void EndBackgroundImage::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);

	spriteRenderer->GetImage(L"./Resource/Map/Background_End.png", false);
	spriteRenderer->GetImageInfo(L"End", L"./Resource/Map/BackgroundSize.csv");

	transform->width = 1024;
	transform->height = 768;
}
