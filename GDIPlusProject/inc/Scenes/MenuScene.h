#pragma once
#include "Manager/GDIPlusManager.h"
#include "Objects/Player.h"
#include "Objects/TestObject.h"

#include "../../inc/GameTime.h"
#pragma comment(lib, "./lib/GameTime.lib")

#include "../../inc/Input.h"
#pragma comment(lib, "./lib/Input.lib")

namespace MenuScene
{
	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC);
	void Update();
	void Render();
	void Uninitialize();
}