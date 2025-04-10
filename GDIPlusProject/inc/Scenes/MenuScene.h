#pragma once
#include "Objects/Player.h"
#include "Objects/TestObject.h"
#include "Scenes/BaseScene.h"

class MenuScene : public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) override;
	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	void Uninitialize() override;

protected:
	HWND g_hwnd;
	HDC g_FrontBufferDC;    // 앞면 DC
	HDC g_BackBufferDC;    // 뒷면 DC
	Gdiplus::Graphics* g_pBackBufferGraphics;
};