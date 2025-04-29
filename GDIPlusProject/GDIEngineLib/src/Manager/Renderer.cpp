#include "pch.h"
#include "Manager/Renderer.h"

Renderer g_Renderer;

void Renderer::Initialize(HWND hWnd, int width, int height)
{
	this->hWnd = hWnd;
	this->width = width;
	this->height = height;

	FrontBufferDC = GetDC(hWnd); //윈도우 클라이언트 영역의 DeviceContext얻기
	BackBufferDC = CreateCompatibleDC(FrontBufferDC); // 호환되는 DeviceContext 생성
	BackBufferBitmap = CreateCompatibleBitmap(FrontBufferDC, width, height); // 메모리 영역생성
	SelectObject(BackBufferDC, BackBufferBitmap); // MemDC의 메모리영역 지정
}

void Renderer::BeginDraw()
{
	PatBlt(BackBufferDC, 0, 0, width, height, BLACKNESS);
}

void Renderer::EndDraw()
{
	BitBlt(FrontBufferDC, 0, 0, width, height, BackBufferDC, 0, 0, SRCCOPY);
}

void Renderer::Shutdown()
{
	DeleteObject(BackBufferBitmap);
	DeleteDC(BackBufferDC);

	FrontBufferDC = nullptr;
	BackBufferDC = nullptr;
	BackBufferBitmap = nullptr;
}

HDC Renderer::GetFrontBuffer()
{
	return FrontBufferDC;
}

HDC Renderer::GetBackBuffer()
{
	return BackBufferDC;
}