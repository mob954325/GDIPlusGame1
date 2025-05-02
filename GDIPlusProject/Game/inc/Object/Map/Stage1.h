#pragma once
#include <vector>
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Object/GroundObject.h"
#include "Object/Item/Apple.h"
#include "Object/TerrainObject.h"

class Stage1 : public GameObject
{
public:
	Stage1(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Stage1();
	void Initialize() override;

	//std::vector<GroundObject*> groundList;
	std::vector<TerrainObject*> groundList;
	std::vector<Apple*> apples;
private:
	void SetGrounds();
	Gdiplus::Graphics* graphics;
	std::vector<int> tileInfo;  // 맵을 그릴 타일 데이터 컨테이너
	int mapWidth = 0;			// 맵 넓이
};

