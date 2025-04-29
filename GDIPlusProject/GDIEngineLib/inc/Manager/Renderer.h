#pragma once
class Renderer
{
public:
	Renderer() = default;			// 다른 생성을 통한 생성자 호출은 금지
	~Renderer() = default;

	void Initialize(HWND hWnd, int width, int height);
	void BeginDraw();
	void EndDraw();
	void Shutdown();

	HDC GetFrontBuffer();
	HDC GetBackBuffer();

private:
	HWND hWnd = {};
	HBITMAP BackBufferBitmap = {};
	HDC FrontBufferDC = {};
	HDC BackBufferDC = {};

	int width = 0;
	int height = 0;
	bool initialized = false;
};

extern Renderer g_Renderer;