#include "Objects/TestObject.h"

TestObject::TestObject()
{
	transform->position = Vector2(100, 100);

	spriteRenderer = AddComponent<SpriteRenderer>();
	collider = new SpriteCollider();
	collider = AddComponent<SpriteCollider>();

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;
}

TestObject::TestObject(int positionX, int positionY)
{
	transform->position = Vector2(positionX, positionY);

	spriteRenderer = AddComponent<SpriteRenderer>();
	collider = AddComponent<SpriteCollider>();

	animationGameTimer = 0.0f;
	maxAnimationGameTime = 0.1f;
}

TestObject::~TestObject()
{
	spriteRenderer->DeleteImage();
	printf("testObject 소멸자 호출\n"); // 임시
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

void TestObject::OnColliderOverlap(GameObject* other)
{
	printf("테스트 오브젝트 충돌 \n");
}