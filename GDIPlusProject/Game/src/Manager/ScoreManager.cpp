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

void ScoreManager::GetScoreString(wchar_t** buffer)
{
	*buffer = new wchar_t[32]; // ? Leak

	wchar_t textBuffer[32] = L"Score : ";
	wchar_t scoreBuffer[32] = L"\0";
	
	_itow_s(score, scoreBuffer, 10);
	int scoreLen = (int)wcslen(scoreBuffer);
	wcscat_s(scoreBuffer, L"\0");
	wcscat_s(textBuffer, scoreBuffer);
	wcscat_s(textBuffer, L"\0");

	wcscpy_s(*buffer, 32, textBuffer);
}
