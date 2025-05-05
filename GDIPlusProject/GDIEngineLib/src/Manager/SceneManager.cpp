#include "pch.h"
#include "Manager/SceneManager.h"

SceneManager g_SceneManager;

void SceneManager::Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	this->hwnd = hwnd;
	this->frontBufferDC = frontBufferDC;
	this->backBufferDC = backBufferDC;
	currentScene = nullptr;
}

void SceneManager::Update()
{
	// 씬 변경
	if (nextScene)
	{
		if (currentScene)
			currentScene->Exit();

		currentScene = nextScene;
		nextScene = nullptr;

		currentScene->Enter(hwnd, frontBufferDC, backBufferDC);
	}

	// 현재 업데이트
	if (currentScene)
	{
		currentScene->PhysicsUpdate();
		currentScene->Update();
	}
}

void SceneManager::Render()
{
	if (currentScene) currentScene->Render();
}

void SceneManager::ChangeScene(int index)
{
	if (index >= scenes.size()) return; // 범위 초과
	
	nextScene = scenes[index];
}

void SceneManager::Shutdown()
{
	for (auto& scene : scenes)
	{
		delete scene;
	}
	scenes.clear();

	currentScene = nullptr;
	nextScene = nullptr;
}