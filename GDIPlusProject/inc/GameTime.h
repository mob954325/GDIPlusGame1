#pragma once
#include <iostream>
#include <windows.h>

namespace GameTime
{
	void InitTime();
	void UpdateTime();

	float GetDeltaTime();
	float GetElapsedTime();
}