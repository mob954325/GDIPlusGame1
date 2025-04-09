#pragma once
#include "Scenes/BaseScene.h"

class PlayScene : public BaseScene
{
public:
	~PlayScene();

	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) override;
	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	void Uninitialize() override;
};