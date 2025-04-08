#include "Objects/TestObject.h"

TestObject::TestObject()
{
	transform.position = Vector2(100, 100);
	spriteRenderer = {};

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;

	target = NULL;
	collider = SpriteCollider();
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

	collider.UpdateValue(*this, spriteRenderer);
	if (target != NULL)
	{
		bool check = collider.IsOverlap(collider, *target);
		if (check) printf("%s, %s이 서로 충돌함\n", typeid(*this).name(), typeid(*this).name());
	}
}

void TestObject::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer.DrawImage(graphics, (int)transform.position.x, (int)transform.position.y);
	collider.RenderCollider(graphics);
}

void TestObject::Uninitialize()
{
	spriteRenderer.DeleteImage();
}

void TestObject::GetTargetCollider(SpriteCollider* targetCollider)
{
	target = targetCollider;
}