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
	if (buffer == nullptr || *buffer == nullptr) return; // null 확인

	wchar_t textBuffer[32] = L"Score : ";
	wchar_t scoreBuffer[16]; // 점수는 작으니 16이면 충분

	_itow_s(score, scoreBuffer, 10);
	wcscat_s(textBuffer, scoreBuffer);

	wcscpy_s(*buffer, 32, textBuffer);
}
