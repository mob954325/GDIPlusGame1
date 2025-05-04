#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"
#include "framework.h"

#include <vector>
#include <windows.h>

class TerrainObject : public GameObject
{
public:
	TerrainObject(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~TerrainObject();

	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;
	void SetupTransform(int gridX, int gridY);

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

	std::vector<GameObject*> groundList;

protected:
	Gdiplus::Bitmap* CreateTilemapBitMap(int row, int cols, std::vector<int> tileData, Gdiplus::Image* tileset);

	Gdiplus::Graphics* graphics = nullptr;
	std::vector<int> tileInfo;  // 맵을 그릴 타일 데이터 컨테이너
	Gdiplus::Image* tileSet = nullptr;
	Gdiplus::Bitmap* tilemapBitmap = nullptr;

	int mapGridXCount = 0;
	int mapGridYCount = 0;
	int tileSize = 0;
	int tileGridXCount = 0;
	int tileGridYCount = 0;
};

