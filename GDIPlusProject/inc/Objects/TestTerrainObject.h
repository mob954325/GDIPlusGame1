#pragma once
#include "Objects/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"

class TestTerrainObject : public GameObject
{
public:
	TestTerrainObject();
	~TestTerrainObject();

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	SpriteRenderer* tileSprite;
	SpriteCollider* collider;

private:
	int tiles[10][10] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1},
	};
};