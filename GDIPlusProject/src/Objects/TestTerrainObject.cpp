#include "Objects/TestTerrainObject.h"

TestTerrainObject::TestTerrainObject()
{
	tileSprite = {};
	//collider = {};
	collider = nullptr;
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

	// 콜라이더
	collider = new SpriteCollider*[5];

	// 임시
	SetCollider();
	//int top = tileSprite->imageHeight * 8;
	//int right = tileSprite->imageWidth * 10;
	//int bottom = tileSprite->imageHeight * 10;

	//collider->bound = { 0, tileSprite->imageHeight * 10, tileSprite->imageWidth * 10, tileSprite->imageHeight * 9 };
	//collider->bound = { 0, 20, 20, 0};
	//AddComponet(collider);
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
		comp->SetIsGround(true);
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
				AddComponet(collider[colliderIndex]);
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
