#include "Manager/GameManager.h"
#include "Manager/SceneManager.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"
#include "Manager/ScoreManager.h"
#include "Manager/TextManager.h"
#include <string>

GameManager g_GameManager;

void GameManager::Initialize(Gdiplus::Graphics* g)
{
	graphics = g;
	g_ScoreManager.ResetData();
	g_TextManager.Initialize(graphics);
}

void GameManager::StartCurrentScene()
{
	g_GameTime.InitTime();
	gameState = GameState::Playing;
}

void GameManager::ShowResultAtScene(bool isClear)
{
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0)); // 완전한 검정색
	graphics->FillRectangle(&blackBrush, (INT)(g_WindowConfig.windowWidth / 2), (INT)(g_WindowConfig.windowHeight / 2), 200, 200);
	
	if (isClear)
	{
		g_TextManager.DrawTextByViewport(L"Clear !!!", 0.5f, 0.2f, Gdiplus::Color::Green);
	}
	else
	{
		g_TextManager.DrawTextByViewport(L"Fail ...", 0.5f, 0.2f, Gdiplus::Color::Red);
	}

	std::wstring str = g_ScoreManager.GetScoreString();
	g_TextManager.DrawTextByViewport(str, 0.5f, 0.3f, Gdiplus::Color::White);
	if(elapsedTime == -1.0f) elapsedTime = g_GameTime.GetElapsedTime();

	std::wstring timeStr = std::to_wstring(elapsedTime);
	g_TextManager.DrawTextByViewport(timeStr, 0.5f, 0.4f, Gdiplus::Color::White);
}

int GameManager::GetStageNumber()
{
	return stageNum;
}

void GameManager::IncreaseStageNumber()
{
	stageNum++;
}

int GameManager::GetMaxStageNumber()
{
	return maxStageNum;
}

void GameManager::ResetStageNumber()
{
	stageNum = 1;
}
