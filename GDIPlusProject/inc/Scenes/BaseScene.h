#pragma once
#include "Manager/UtilityManager.h"
#include "Manager/GDIPlusManager.h"

class BaseScene
{
public:
	virtual ~BaseScene() {};

	virtual void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) = 0;
	virtual void PhysicsUpdate() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Uninitialize() = 0;
};