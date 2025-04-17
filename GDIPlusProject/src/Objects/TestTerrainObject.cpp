#include "Objects/TestTerrainObject.h"

TestTerrainObject::TestTerrainObject()
{
	tileSprite = {};
	collider = nullptr;
}

TestTerrainObject::~TestTerrainObject()
{
	tileSprite->DeleteImage();
}

void TestTerrainObject::Initialize()
{
	tileSprite = AddComponent<SpriteRenderer>();

	tileSprite->GetImage(L"./Resource/BackGround/Yellow.png");
	tileSprite->GetImageInfo(L"Yellow", L"./Resource/Background/mapSize.csv");

	collider = new SpriteCollider*[5];
	SetCollider();
}

void TestTerrainObject::Update()
{
	//collider->UpdateValue(this, tileSprite);
}

void TestTerrainObject::Render(Gdiplus::Graphics* graphics)
{
	for (int y = 0; y < tilesYCount; y++)
	{
		for (int x = 0; x < tilesXCount; x++)
		{
			if (tiles[y][x] == 1)
			{
				tileSprite->DrawImage(graphics, x * tileSprite->imageWidth, y * tileSprite->imageHeight);
			}
		}
	}

	for (int i = 0; i < blockCount; i++)
	{
		collider[i]->RenderCollider(graphics);
	}
}

void TestTerrainObject::OnColliderOverlap(GameObject* other)
{
	Gravity* comp = other->GetComponent<Gravity>();


	if (comp != nullptr)
	{
		// 블록 충돌 체크
		comp->SetIsGround(true);

		if (!comp->GetIsGround()) playerTransform = *other->transform; // 지형에 닿았으면 닿은 위치 갱신

		// 블록 위가 아닌 위치에 플레이어가 충돌 할 때 체크
		// 블록 아래
		if (other->transform->position.y - playerTransform.position.y < 0.0f) 
		{
			// note : 위로 올라간다 -> y값이 -값이 추가된다.
			printf("머리 부딪침\n");
			other->transform->SetTransform(playerTransform.position + Vector2(0, 5));
			comp->SetIsGround(false);
		}

		// 블록 왼쪽
		if (other->transform->position.x - playerTransform.position.x > 0.0f)
		{
			printf("왼쪽 부딪힘\n");
			//other->transform->SetTransform(playerTransform.position + Vector2(-5, 0));
			//comp->SetIsGround(false);
		}

		// 블록 오른쪽
		if (other->transform->position.x - playerTransform.position.x < 0.0f)
		{
			printf("오른쪽 부딪힘\n");
			//other->transform->SetTransform(playerTransform.position + Vector2(5, 0));
			//comp->SetIsGround(false);
		}
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

// 이건 완료
void TestTerrainObject::SetCollider()
{
	// 가로만 생성하기 -> 일단 모든 지형이 높이가 1인 사각형일 때만 가정함
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	int colliderIndex = 0;
	for (int y = 0; y < tilesYCount; y++)
	{
		bool isVaild = false;
		int rightCount = 0;
		for (int x = 0; x < tilesXCount; x++)
		{
			if (!isVaild && tiles[y][x] == 1)
			{
				collider[colliderIndex] = new SpriteCollider();
				collider[colliderIndex] = AddComponent<SpriteCollider>();
				collider[colliderIndex]->bound = {x * tileSprite->imageWidth, 
												(y + 1) * tileSprite->imageHeight, 
												(x) * tileSprite->imageWidth, 
												(y) * tileSprite->imageHeight};
				isVaild = true;
			}

			if (isVaild && tiles[y][x] == 1) // x 방향으로 늘어남
			{
				rightCount++;
			}

			if (isVaild && (tiles[y][x] == 0 || x == tilesXCount - 1)) // 지형이 아닌 구역에 도달 or 맵 끝에 도달
			{
				// bound 설정
				collider[colliderIndex]->bound.right += rightCount * tileSprite->imageWidth;
				colliderIndex++;
				rightCount = 0;
				isVaild = false;
			}
		}
	}
	
	int a = 0;
}
