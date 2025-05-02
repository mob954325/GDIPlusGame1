#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"

#include <vector>

class TerrainObject : public GameObject
{
public:
	TerrainObject(Gdiplus::Graphics* g, int tileType) : graphics(g), tileNumber(tileType) { Initialize(); }
	~TerrainObject();

	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;
	void SetupTransform(int gridX, int gridY);

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer;
	Collider* collider;

	int tileNumber = 0;
};

