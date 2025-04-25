#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"

#include "Component/SpriteRenderer.h"
#include "Component/Collider.h"

class Apple : public GameObject
{
public:
	Apple(Gdiplus::Graphics* g) : graphics(g) { Initialize(); };

	void Initialize() override;
	void Update() override;
	void Render() override;

	// Event
	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderStayImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

	void SetupTransform(int gridX, int gridY, int countX, int countY);

private:
	Gdiplus::Graphics* graphics;
	SpriteRenderer* spriteRenderer;	
	Collider* collider;

	float animationGameTimer = 0.0f;
	float maxAnimationGameTime = 0.05f;
};