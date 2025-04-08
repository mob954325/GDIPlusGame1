#include "Objects/TestObject.h"

TestObject::TestObject()
{
	transform.position = Vector2(100, 100);
	spriteRenderer = {};

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;
}

void TestObject::Initialize()
{
	spriteRenderer.GetImage(L"./Resource/Test/walk-Sheet.png");
	spriteRenderer.GetImageInfo(L"Walk", L"./Resource/Test/animSize.csv");
}

void TestObject::Update()
{
	animationGameTimer += GameTime::GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer.currFrame++;
		spriteRenderer.currFrame %= spriteRenderer.imageFrameCount;
	}
}

void TestObject::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer.DrawImage(graphics, transform.position.x, transform.position.y);
}

void TestObject::Uninitialize()
{
	spriteRenderer.DeleteImage();
}