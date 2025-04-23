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
	void Update() override;
	void Render() override;
	void SetupTransform(int gridX, int gridY, int countX, int countY);

	// Event
	void OnColliderEnter(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;

protected:
	Gdiplus::Graphics* graphics = {};
	SpriteRenderer* spriteRenderer;
	Collider* collider;
};

