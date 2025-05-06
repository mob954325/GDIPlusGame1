#include "Object/MenuBackgroundImage.h"

MenuBackgroundImage::~MenuBackgroundImage()
{
}

void MenuBackgroundImage::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);

	spriteRenderer->GetImage(L"./Resource/Map/Background.png", false);
	spriteRenderer->GetImageInfo(L"Menu", L"./Resource/Map/BackgroundSize.csv");

	transform->width = 1024;
	transform->height = 768;
}