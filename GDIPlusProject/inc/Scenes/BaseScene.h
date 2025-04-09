#pragma once
#include "Manager/UtilityManager.h"
#include "Manager/GDIPlusManager.h"

class BaseScene
{
public:
	virtual ~BaseScene();

	virtual void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC);
	virtual void PhysicsUpdate();
	virtual void Update();
	virtual void Render();
	virtual void Uninitialize();
};