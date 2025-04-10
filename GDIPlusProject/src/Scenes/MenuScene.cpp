#include "Scenes/MenuScene.h"

MenuScene::MenuScene()
{
	g_hwnd = {};
	g_FrontBufferDC = {};    // 앞면 DC
	g_BackBufferDC = {};    // 뒷면 DC
	g_pBackBufferGraphics = {};

	player = nullptr;
	testObj = nullptr;
}

MenuScene::~MenuScene()
{
	delete g_pBackBufferGraphics;
}

void MenuScene::Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	g_hwnd = hwnd;
	g_FrontBufferDC = frontBufferDC;
	g_BackBufferDC = backBufferDC;

	g_pBackBufferGraphics = Gdiplus::Graphics::FromHDC(g_BackBufferDC);

	player = new Player();
	player->Initialize();

	testObj = new TestObject();
	testObj->Initialize();
}

void MenuScene::PhysicsUpdate()
{
	SpriteCollider* playerCollider = player->GetComponent<SpriteCollider>();
	testObj->OnColliderOverlap(playerCollider);
}

void MenuScene::Update()
{
	PhysicsUpdate(); // 임시
	testObj->Update();
	player->Update();
}

void MenuScene::Render()
{
	testObj->Render(g_pBackBufferGraphics); // TODO 랜더 동작 안됨
	player->Render(g_pBackBufferGraphics);
}

void MenuScene::Uninitialize()
{
}

// 안쓰는 함수
//void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap);
//void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap)
//{
//	if (bitmap->GetLastStatus() != Gdiplus::Ok)
//	{
//		MessageBox(hwnd, L"PNG 파일 로드 실패", L"오류", MB_ICONERROR);
//		PostQuitMessage(0);
//	}
//}