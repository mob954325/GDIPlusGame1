#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/Scene.h"
#include "Object/MainCamera.h"

// NOTE: 카메라 이동 작성

class PlayScene : public Scene
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
		Gdiplus::GdiplusShutdown(gdiPlusToken); 
	};

protected:
	float sceneTimer = 0;
	float sceneMaxTimer = 10;
	
	int scoreBufferSize = 20;
	wchar_t* scoreBuffer;

	HWND hwnd = {};
	HDC FrontBufferDC = {};    // 앞면 DC
	HDC BackBufferDC = {};    // 뒷면 DC

	ULONG_PTR gdiPlusToken = 0;
	Gdiplus::GdiplusStartupInput gsi = {};
	Gdiplus::Graphics* graphics = {};

	MainCamera* mainCamera = {};
};
