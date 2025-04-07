#pragma once
#include <Windows.h>

namespace Renderer
{
	void Initialize(HWND hwnd, int width, int height);
	void BeginDraw();
	void EndDraw();
	void Uninitialize();

	HDC GetFrontBuffer();
	HDC GetBackBuffer();
}