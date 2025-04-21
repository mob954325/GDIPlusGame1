#pragma once
#include <Windows.h>

class Input
{
public:
	Input() = default;
	~Input() = default;

	void Update();
	bool IsKeyDown(int vKey);
	bool IsKeyPressed(int vKey);
	bool IsKeyReleased(int vKey);

private:
	SHORT prevState[256] = { 0 };
	SHORT currState[256] = { 0 };
};

extern Input g_Input;