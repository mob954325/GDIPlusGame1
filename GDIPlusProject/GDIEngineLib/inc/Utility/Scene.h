#pragma once
#include "windows.h"
#include "GameObject.h"
#include <set>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() { Clear(); }


	void Clear();
	void CheckObjects();
	virtual void Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC) = 0;
	virtual void PhysicsUpdate();
	virtual void Update();
	virtual void Render();
	virtual void Exit() { Clear(); };

	// 해당 씬이 가지고 있는 오브젝트 리스트
	std::vector<GameObject*> gameObjectList;
	std::vector<GameObject*> gameObjectDeleteList;
	std::set<std::pair<GameObject*, GameObject*>> previousCollisions;
	std::set<std::pair<GameObject*, GameObject*>> currentCollisions;
};