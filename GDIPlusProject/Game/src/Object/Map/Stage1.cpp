#include "Object/Map/Stage1.h"

#include "Object/Enemy.h"

Stage1::~Stage1()
{
}

void Stage1::Initialize()
{
	groundList.reserve(8);
	enemies.reserve(8);
	SetGrounds();
}

void Stage1::SetGrounds()
{
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	int groundIndex = 0;
	for (int y = 0; y < tilesYCount; y++)
	{
		bool isVaild = false;
		int rightCount = 0, firstVaildGridX;
		for (int x = 0; x < tilesXCount; x++)
		{
			if (tiles[y][x] == 2)
			{
				Enemy* enemy = new Enemy(graphics);
				enemies.push_back(enemy); // 임시
				enemy->transform->SetTransform(x * 32, y * 32);
			}

			if (!isVaild && tiles[y][x] == 1)
			{
				groundList.push_back(new GroundObject(graphics));
				firstVaildGridX = x;
				isVaild = true;
			}

			if (isVaild && tiles[y][x] == 1) // x 방향으로 늘어남
			{
				rightCount++;
			}

			if (isVaild && (tiles[y][x] == 0 || x == tilesXCount - 1)) // 지형이 아닌 구역에 도달 or 맵 끝에 도달
			{
				// bound 설정
				groundList[groundIndex]->SetupTransform(firstVaildGridX, y, rightCount, 1); // 콜라이더 값이 제대로 안들어감
				groundIndex++;
				rightCount = 0;
				isVaild = false;
			}
		}
	}
}
