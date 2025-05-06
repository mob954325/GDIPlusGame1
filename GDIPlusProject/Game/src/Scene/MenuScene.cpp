#include "framework.h"
#include "Scene/MenuScene.h"
#include "GDIEngineLib/inc/Manager/Input.h"
#include "GDIEngineLib/inc/Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/ScoreManager.h"
#include "Manager/TextManager.h"
#include "Object/MenuBackgroundImage.h"

void MenuScene::Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	this->hwnd = hwnd;
	this->FrontBufferDC = frontBufferDC;	// 앞면 DC
	this->BackBufferDC = backBufferDC;	// 뒷면 DC

	Gdiplus::GdiplusStartup(&gdiPlusToken, &gsi, nullptr);
	this->graphics = Gdiplus::Graphics::FromHDC(BackBufferDC);

	gameObjectList.push_back(new MenuBackgroundImage(graphics));

	g_GameManager.Initialize(graphics);
	g_GameManager.ResetStageNumber();
	g_ScoreManager.ResetData();
	g_SoundManager.Initialize();
	g_SoundManager.PlayMainMusic("./Resource/Sound/MenuBGM.wav");
}

void MenuScene::PhysicsUpdate()
{
}

void MenuScene::Update(){

	if (g_Input.IsKeyPressed(VK_SPACE)) g_SceneManager.ChangeScene(1);
	g_SoundManager.Update();
}

void MenuScene::Render()
{
	for (GameObject* obj : gameObjectList)
	{
		if (obj == nullptr) continue;

		obj->Render();
	}

	g_TextManager.DrawTextByViewport(L"Pixel Adventure", 0.5f, 0.3f, Gdiplus::Color::Black);
	g_TextManager.DrawTextByViewport(L"조작키", 0.49f, 0.36f, Gdiplus::Color::Black);
	g_TextManager.DrawTextByViewport(L"이동 : 화살표 좌우", 0.49f, 0.4f, Gdiplus::Color::Black);
	g_TextManager.DrawTextByViewport(L"점프 : 화살표 위", 0.48f, 0.45f, Gdiplus::Color::Black);
	g_TextManager.DrawTextByViewport(L"스테이지 재시작 : R", 0.5f, 0.5f, Gdiplus::Color::Black);
	g_TextManager.DrawTextByViewport(L"[ Space Bar ] - Start", 0.5f, 0.7f, Gdiplus::Color::Black);
}
