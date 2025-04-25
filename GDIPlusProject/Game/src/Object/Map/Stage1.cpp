#include "Object/Map/Stage1.h"

Stage1::~Stage1()
{
}

void Stage1::Initialize()
{
	groundList.reserve(8);
	apples.reserve(8);
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
				Apple* apple = new Apple(graphics);
				apples.push_back(apple); // 임시
				apple->SetupTransform(x, y, rightCount, 1);
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
