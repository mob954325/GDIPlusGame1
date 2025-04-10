#pragma once
#include "Scenes/BaseScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/PlayScene.h"

/// 씬 관리 매니저
/// 여러 씬을 관리하고 메인에 사용할 씬을 설정하는 매니저
enum SceneType
{
	MENU = 0,
	PLAY,
	//END,
	SCENECOUNT
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void UnInitialize();
	void ChangeCurrnetScene(SceneType type);
	BaseScene* GetCurrentScene(); 
private:
	BaseScene* SceneList[SceneType::SCENECOUNT];
	BaseScene* currentScene;
};

