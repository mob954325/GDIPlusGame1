#pragma once
#include "Objects/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Component/Gravity.h"

class TestTerrainObject : public GameObject
{
public:
	TestTerrainObject();
	~TestTerrainObject();

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	void OnColliderOverlap(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;
	SpriteRenderer* tileSprite;
	SpriteCollider** collider;

	int tilesXCount = 12;
	int tilesYCount = 12;
	int blockCount = 5;

private:
	int tiles[12][12] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1},
	};

	void SetCollider();
};