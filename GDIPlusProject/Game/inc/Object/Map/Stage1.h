#pragma once
#include <vector>
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Object/GroundObject.h"
#include "Object/Item/Apple.h"

class Stage1 : public GameObject
{
public:
	Stage1(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Stage1();
	void Initialize() override;

	std::vector<GroundObject*> groundList;
	std::vector<Apple*> apples;
private:
	Gdiplus::Graphics* graphics;

	void SetGrounds();
	int tilesYCount = 12;
	int tilesXCount = 16;

	// ㅁㅁ
	int tiles[12][16] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
		{0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
		{0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
};

