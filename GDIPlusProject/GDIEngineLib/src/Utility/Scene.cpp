#include "pch.h"
#include "Utility/Scene.h"

void Scene::Clear()
{
	for (auto& gameObject : gameObjectList)
	{
		delete gameObject;
	}
	
	gameObjectList.clear();
	previousCollisions.clear();
	currentCollisions.clear();
}

void Scene::CheckObjects()
{
	// 리스트에서 오브젝트 제거될 오브젝트 넘기기
	if (gameObjectList.size() <= 0) return;

	for (auto it = gameObjectList.begin(); it != gameObjectList.end();)
	{
		if ((*it)->shouldBeDeleted)
		{
			gameObjectDeleteList.push_back(*it);
			it = gameObjectList.erase(it);
		}
		else
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
