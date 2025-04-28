#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"

class GroundObject : public GameObject
{
public:
	GroundObject(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~GroundObject();

	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;
	void SetupTransform(int gridX, int gridY, int countX, int countY);

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

protected:
	Gdiplus::Graphics* graphics = {};
	SpriteRenderer* spriteRenderer;
	Collider* collider;
};

