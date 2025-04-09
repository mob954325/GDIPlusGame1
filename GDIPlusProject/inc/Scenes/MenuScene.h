#pragma once
#include "Objects/Player.h"
#include "Objects/TestObject.h"

namespace MenuScene
{
	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC);
	void PhysicsUpdate();
	void Update();
	void Render();
	void Uninitialize();
}