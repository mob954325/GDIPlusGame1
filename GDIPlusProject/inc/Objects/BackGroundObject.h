#pragma once
#include "Manager/SettingManager.h"
#include "Objects/GameObject.h"
#include "Component/SpriteRenderer.h"

class BackGroundObject : public GameObject
{
public:
	BackGroundObject();
	~BackGroundObject();

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	SpriteRenderer* spriteRenderer;

	int widthCount;
	int heightCount;
};