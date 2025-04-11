#pragma once
#include "Manager/UtilityManager.h"
#include "Manager/GDIPlusManager.h"
#include "Objects/GameObject.h"

#include <vector>

class BaseScene
{
public:
	virtual ~BaseScene() {};

	virtual void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) = 0;
	virtual void PhysicsUpdate() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Uninitialize() = 0;

	// 해당 씬이 가지고 있는 오브젝트 리스트
	std::vector<GameObject*> gameObjectList;

	// 임시
	std::vector<GameObject*> mapObjectList;
};