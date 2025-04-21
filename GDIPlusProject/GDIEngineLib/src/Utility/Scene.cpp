#include "pch.h"
#include "Utility/Scene.h"

void Scene::Clear()
{
	for (auto& gameObject : gameObjectList)
	{
		delete gameObject;
	}
	
	gameObjectList.clear();
}

void Scene::CheckObjects()
{
	// 리스트에서 오브젝트 제거하기
	for (auto& gameObject : gameObjectList)
	{
		if (gameObject->shouldBeDeleted)
		{
			auto it = std::find(gameObjectList.begin(), gameObjectList.end(), gameObject);
			if (it != gameObjectList.end())
			{
				delete gameObject;
				gameObjectList.erase(it); // 오브젝트 제거
			}
		}
	}
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
