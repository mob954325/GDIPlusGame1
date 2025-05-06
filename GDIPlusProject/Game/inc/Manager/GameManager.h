#pragma once
#include "framework.h"

enum GameState
{
	Ready = 0,
	Playing,
	End
};

class GameManager
{
public:
	GameState gameState = GameState::Ready;
	void Initialize(Gdiplus::Graphics* g);
	void StartCurrentScene();
	void ShowResultAtScene(bool isClear);

	int GetStageNumber();
	int GetMaxStageNumber();
	void IncreaseStageNumber();
	void ResetStageNumber();


protected:
	Gdiplus::Graphics* graphics;
	int currentSceneIndex = 0;
	float elapsedTime = -1.0f;
	int stageNum = 1;
	int maxStageNum = 2;
};

extern GameManager g_GameManager;