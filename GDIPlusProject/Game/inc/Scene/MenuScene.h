#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/Scene.h"
#include "Manager/SoundManager.h"

class MenuScene : public Scene
{
public:
	void Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) override;
	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	void Exit() override 
	{ 
		Clear(); 
		delete graphics;
		g_SoundManager.Release();
		Gdiplus::GdiplusShutdown(gdiPlusToken); 
	};

protected:
	HWND hwnd = nullptr;
	HDC FrontBufferDC = nullptr;    // 앞면 DC
	HDC BackBufferDC = nullptr;    // 뒷면 DC

	ULONG_PTR gdiPlusToken = 0;
	Gdiplus::GdiplusStartupInput gsi = nullptr;
	Gdiplus::Graphics* graphics = nullptr;
};

