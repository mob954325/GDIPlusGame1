#include "../../inc/Scenes/MenuScene.h"

namespace MenuScene
{
	void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap);

	HWND g_hwnd;
	HDC g_FrontBufferDC;    // 앞면 DC
	HDC g_BackBufferDC;    // 뒷면 DC

	Gdiplus::Graphics* g_pBackBufferGraphics;

	Player player;
	TestObject testObj;


	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
	{
		g_hwnd = hwnd;
		g_FrontBufferDC = frontBufferDC;
		g_BackBufferDC = backBufferDC;

		g_pBackBufferGraphics = Gdiplus::Graphics::FromHDC(g_BackBufferDC);

		player.Initialize();
		testObj.Initialize();
	}

	void Update()
	{
		testObj.Update();
		player.Update();
	}

	void Render()
	{
		testObj.Render(g_pBackBufferGraphics);
		player.Render(g_pBackBufferGraphics);
	}

	void Uninitialize()
	{
		player.Uninitialize();
	}

	void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap)
	{
		if (bitmap->GetLastStatus() != Gdiplus::Ok)
		{
			MessageBox(hwnd, L"PNG 파일 로드 실패", L"오류", MB_ICONERROR);
			PostQuitMessage(0);
		}
	}
}