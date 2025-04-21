#pragma once
#include "framework.h"

class ScoreManager
{
public:
	ScoreManager() = default;
	~ScoreManager() = default;

	void ResetData();
	void AddScore();
	void GetScoreString(wchar_t** buffer);

private:
	Gdiplus::Graphics* graphics = {};
	int score = 0;
};

extern ScoreManager g_ScoreManager;

