#include "pch.h"
#include "Utility/Scene.h"

void Scene::Clear()
{
	for (auto& gameObject : gameObjectList)
	{
		delete gameObject;
	}
	gameObjectList.clear();

	for (auto& object : gameObjectDeleteList)
	{
		delete object;
	}
	gameObjectDeleteList.clear();

	previousCollisions.clear();
	currentCollisions.clear();
}

void Scene::CheckObjects()
{
	// 리스트에서 오브젝트 제거될 오브젝트 넘기기
	if (gameObjectList.empty()) return;

	for (auto it = gameObjectList.begin(); it != gameObjectList.end();)
	{
		if ((*it) == nullptr) // 외부에서 객체가 삭제당함			
		{
			it = gameObjectList.erase(it);
		}
		else if ((*it)->shouldBeDeleted) // 삭제 예정
		{
			gameObjectDeleteList.push_back(*it);
			it = gameObjectList.erase(it);
		}
		else // 삭제할 오브젝트가 아님
		{
			++it;
		}
	}
}

void Scene::DeleteDeactiveObjects()
{
	// 제거될 오브젝트 제거하기
	for (auto& object : gameObjectDeleteList)
	{
		delete object;
	}
	gameObjectDeleteList.clear();
}

void Scene::PhysicsUpdate()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
}
