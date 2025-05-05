#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"

class GroundObject : public GameObject
{
public:
	GroundObject() { Initialize(); }
	~GroundObject();

	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;
	void SetupTransform(int gridSize, int gridX, int gridY, int countX, int countY);

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

protected:
	Collider* collider;
};

