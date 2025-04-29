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
	if (*buffer == nullptr) return; // 출력할 내용이 존재하지 않음

	wchar_t textBuffer[32] = L"Score : ";
	wchar_t scoreBuffer[32] = L"\0";
	
	_itow_s(score, scoreBuffer, 10);
	int scoreLen = (int)wcslen(scoreBuffer);
	wcscat_s(scoreBuffer, L"\0");
	wcscat_s(textBuffer, scoreBuffer);
	wcscat_s(textBuffer, L"\0");

	// buffer == NULL -> 씬 교체 시 발생
	wcscpy_s(*buffer, 32, textBuffer); // ((destination)) != NULL && ((size_in_elements)) > 0 
}
