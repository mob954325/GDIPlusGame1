#include "Manager/SceneManager.h"

SceneManager::SceneManager()
{
	currentScene = nullptr;
	SceneList[SceneType::MENU] = new MenuScene();
	SceneList[SceneType::PLAY] = new PlayScene();
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < (int)SceneType::SCENECOUNT; i++)
	{
		delete SceneList[i];
	}
}

void SceneManager::Initialize()
{
	currentScene = SceneList[SceneType::MENU];
}

void SceneManager::UnInitialize()
{

}

void SceneManager::ChangeCurrnetScene(SceneType type)
{
	if ((int)type >= SceneType::SCENECOUNT || (int)type < 0) return; // 존재하지 않는 씬

	// TODO 나중에 메뉴- 플레이씬들 전환할 때 초기화 하거나, 
	// 플레이 씬 사이에 교체할 때 버퍼 초기화 해야할듯
	currentScene = SceneList[(int)type];
}

BaseScene* SceneManager::GetCurrentScene()
{
	return currentScene;
}
