#include "Object/GroundObject.h"
#include "Component/Gravity.h"

GroundObject::~GroundObject()
{
}

void GroundObject::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	collider = AddComponent<Collider>();

	spriteRenderer->GetImage(L"./Resource/Map/Blue.png");
	spriteRenderer->GetImageInfo(L"Blue", L"./Resource/Map/mapSize.csv");
}

void GroundObject::Update()
{
}

void GroundObject::Render()
{
	for (int y = 0; y < transform->height / spriteRenderer->imageHeight; y++)
	{
		for (int x = 0; x < transform->width / spriteRenderer->imageWidth; x++)
		{
			spriteRenderer->DrawImage(graphics, (int)(transform->position.x + x * spriteRenderer->imageWidth), (int)(transform->position.y + y * spriteRenderer->imageHeight));
		}
	}
}

/// NOTE
/// bound left 와 bound right 값이 잘못됨

void GroundObject::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform(gridX * spriteRenderer->imageWidth, gridY * spriteRenderer->imageHeight);

	transform->width = (float)(spriteRenderer->imageWidth * countX);
	transform->height = (float)(spriteRenderer->imageHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)(transform->position.y + transform->height),(LONG)(transform->position.x + transform->width), (LONG)transform->position.y };
	printf("%d, %d, %d, %d\n", collider->bound.left, collider->bound.top, collider->bound.right, collider->bound.bottom);
}

void GroundObject::OnColliderOverlap(GameObject* other)
{
	Gravity* comp = other->GetComponent<Gravity>();

	if (comp != nullptr)
	{
		// 블록 충돌 체크
		comp->SetIsGround(true);

		if (!comp->GetIsGround()) playerTransform = *other->transform; // 지형에 닿았으면 닿은 위치 갱신

		// 블록 위가 아닌 위치에 플레이어가 충돌 할 때 체크
		// 블록 아래
		//if (other->transform->position.y - playerTransform.position.y < 0.0f)
		//{
		//	// note : 위로 올라간다 -> y값이 -값이 추가된다.
		//	printf("머리 부딪침\n");
		//	other->transform->SetTransform(playerTransform.position + Vector2(0, 5));
		//	comp->SetIsGround(false);
		//}

		//// 블록 왼쪽
		//if (other->transform->position.x - playerTransform.position.x > 0.0f)
		//{
		//	printf("왼쪽 부딪힘\n");
		//	//other->transform->SetTransform(playerTransform.position + Vector2(-5, 0));
		//	//comp->SetIsGround(false);
		//}

		//// 블록 오른쪽
		//if (other->transform->position.x - playerTransform.position.x < 0.0f)
		//{
		//	printf("오른쪽 부딪힘\n");
		//	//other->transform->SetTransform(playerTransform.position + Vector2(5, 0));
		//	//comp->SetIsGround(false);
		//}
	}
}

void GroundObject::OnColliderExit(GameObject* other)
{
	Gravity* comp = other->GetComponent<Gravity>();
	
	if (comp != nullptr)
	{
		comp->SetIsGround(false);
	}
}
