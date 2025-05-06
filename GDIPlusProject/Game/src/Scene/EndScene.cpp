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
	g_SoundManager.Initialize();

	g_SoundManager.PlayMainMusic("./Resource/Sound/EndBGM.wav");
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

	g_TextManager.DrawTextByViewport(L"Game Clear !!!", 0.5f, 0.4f, Gdiplus::Color::LawnGreen);
	g_TextManager.DrawTextByViewport(L"[ Space Bar ] - Back to Menu", 0.5f, 0.7f, Gdiplus::Color::Black);
}
