#include "App/GameApp.h"
#include "GDIEngineLib/inc/Manager/SceneManager.h"
#include "Scene/MenuScene.h"
#include "Scene/PlayScene.h"
#include "Scene/EndScene.h"

void GameApp::Initialize()
{
	__super::Initialize();

	g_SceneManager.CreateScene<MenuScene>();
	g_SceneManager.CreateScene<PlayScene>();
	g_SceneManager.CreateScene<EndScene>();

	g_SceneManager.ChangeScene(0); // menu
}

void GameApp::Shutdown()
{
	__super::Shutdown();
}