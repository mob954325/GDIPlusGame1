#include "Objects/TestObject.h"

TestObject::TestObject()
{
	transform->position = Vector2(100, 100);

	spriteRenderer = new SpriteRenderer();
	collider = new SpriteCollider();

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;
}

TestObject::~TestObject()
{
	spriteRenderer->DeleteImage();
}

void TestObject::Initialize()
{
	spriteRenderer->GetImage(L"./Resource/Test/walk-Sheet.png");
	spriteRenderer->GetImageInfo(L"Walk", L"./Resource/Test/animSize.csv");
}

void TestObject::Update()
{
	animationGameTimer += GameTime::GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		spriteRenderer->currFrame++;
		spriteRenderer->currFrame %= spriteRenderer->imageFrameCount;
	}

	collider->UpdateValue(this, spriteRenderer);
}

void TestObject::Render(Gdiplus::Graphics* graphics)
{
	spriteRenderer->DrawImage(graphics, (int)transform->position.x, (int)transform->position.y);
	collider->RenderCollider(graphics);
}

void TestObject::OnColliderOverlap(SpriteCollider* other)
{
	if (collider->IsOverlap(collider, other))
	{
		printf("%s, %s가 서로 충돌함\n", typeid(*this).name(), typeid(*other).name());
	}
}