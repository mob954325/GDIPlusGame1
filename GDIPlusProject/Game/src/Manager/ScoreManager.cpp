#include "Manager/ScoreManager.h"

ScoreManager g_ScoreManager;

void ScoreManager::ResetData()
{
	score = 0;
}

void ScoreManager::AddScore()
{
	score++;
}

std::wstring ScoreManager::GetScoreString()
{
	return L"Score : " + std::to_wstring(score);
}
