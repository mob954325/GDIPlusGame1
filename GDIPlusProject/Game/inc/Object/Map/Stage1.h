#pragma once
#include <vector>
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Object/GroundObject.h"
#include "Object/Enemy.h"

class Stage1 : public GameObject
{
public:
	Stage1(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Stage1();
	void Initialize() override;

	std::vector<GroundObject*> groundList;

	// 임시
	std::vector<Enemy*> enemies;
private:
	Gdiplus::Graphics* graphics;

	void SetGrounds();
	int tilesYCount = 12;
	int tilesXCount = 16;

	int tiles[12][16] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
		{0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
};

