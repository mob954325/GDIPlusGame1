#include "GDIEngineLib/inc/Manager/SceneManager.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "Scene/EndScene.h"
#include "Manager/ScoreManager.h"
#include "Manager/TextManager.h"
#include "Manager/GameManager.h"
#include "Object/EndBackgroundImage.h"

EndScene::~EndScene()
{
}

void EndScene::Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	this->hwnd = hwnd;
	this->FrontBufferDC = frontBufferDC;	// 앞면 DC
	this->BackBufferDC = backBufferDC;	// 뒷면 DC

	Gdiplus::GdiplusStartup(&gdiPlusToken, &gsi, nullptr);
	this->graphics = Gdiplus::Graphics::FromHDC(BackBufferDC);

	gameObjectList.push_back(new EndBackgroundImage(graphics));

	g_GameManager.Initialize(graphics);
}

void EndScene::PhysicsUpdate()
{
}

void EndScene::Update()
{
	if (g_Input.IsKeyPressed(VK_SPACE))
	{
		g_SceneManager.ChangeScene(0);
	}
}

void EndScene::Render()
{
	for (GameObject* obj : gameObjectList)
	{
		if (obj == nullptr) continue;

		obj->Render();
	}

	g_TextManager.DrawTextByViewport(scoreString, 0.5f, 0.3f, Gdiplus::Color::White);
	g_TextManager.DrawTextByViewport(L"[ Space Bar ] - Back to Menu", 0.5f, 0.7f, Gdiplus::Color::White);
}
