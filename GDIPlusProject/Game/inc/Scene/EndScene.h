#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/Scene.h"

class EndScene : public Scene
{
public:
	~EndScene();
	void Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) override;
	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	void Exit() override { Clear(); Gdiplus::GdiplusShutdown(gdiPlusToken); };

protected:
	HWND hwnd = {};
	HDC FrontBufferDC = {};    // 앞면 DC
	HDC BackBufferDC = {};    // 뒷면 DC

	ULONG_PTR gdiPlusToken = 0;
	Gdiplus::GdiplusStartupInput gsi = {};
	Gdiplus::Graphics* graphics = {};

	wchar_t* scoreString = {};
};