#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"
#include "framework.h"

#include <vector>
#include <windows.h>

// 타일 정보
// 콜라이더 이상하게 들어갔으면 데이터(월드명.json)에서 투명 타일 들어갔는지 확인할 것
// 241 : 사과
// 236 : 깃발
// 255 : 스폰 지점

class TerrainObject : public GameObject
{
public:
	TerrainObject(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~TerrainObject();

	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;

	std::vector<GameObject*> groundList;
	std::vector<GameObject*> objectList;
	Vector2 spawnPosition = Vector2();

protected:
	Gdiplus::Bitmap* CreateTilemapBitMap(int rows, int cols, std::vector<int> tileData, Gdiplus::Image* tileset);
	void SetGroundCollider(int rows, int cols, std::vector<int> tileData);

	Gdiplus::Bitmap* CreateBackgroundBitmap(int rows, int cols);
	std::vector<GameObject*> CreateObjects(int rows, int cols, std::vector<int> tileData);


	Gdiplus::Graphics* graphics = nullptr;
	std::vector<int> tileInfo;  // 맵을 그릴 타일 데이터 tileData
	Gdiplus::Image* tileSet = nullptr;
	Gdiplus::Bitmap* tilemapBitmap = nullptr;
	Gdiplus::Bitmap* backgroundBitmap = nullptr;
	Gdiplus::Rect destRect = {};
	Gdiplus::Rect srcRect = {};

	int mapGridXCount = 0;
	int mapGridYCount = 0;
	int tileSize = 0;
	int tileGridXCount = 0;
	int tileGridYCount = 0;
};

