#pragma once
#include "Utility/Scene.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC);
	void Update();
	void Render();
	void ChangeScene(int index);
	void Shutdown();

	template<typename T>
	void CreateScene()
	{
		Scene* scene = new T();
		scenes.push_back(scene);
	}
private:
	std::vector<Scene*> scenes;

	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

	HWND hwnd = {};
	HDC frontBufferDC = {};
	HDC backBufferDC = {};
};

extern SceneManager g_SceneManager;