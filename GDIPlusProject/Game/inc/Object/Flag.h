#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"

class Flag : public GameObject
{
public:
	Flag(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Flag();
	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderStayImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

	void SetupData(int gridSize, int gridX, int gridY, int countX, int countY);

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer = nullptr;
	Collider* collider = nullptr;
};