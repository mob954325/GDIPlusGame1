#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/SceneManager.h"
#include "GDIEngineLib/inc/Manager/Input.h"

#include "Scene/PlayScene.h"
#include "Component/Collider.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/Item/Apple.h"
#include "Object/TerrainObject.h"
#include "Object/Flag.h"
#include "Manager/GameManager.h"

void PlayScene::Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{ 
	// handle, gdi setup
	this->hwnd = hwnd;
	this->FrontBufferDC = frontBufferDC;	// 앞면 DC
	this->BackBufferDC = backBufferDC;	// 뒷면 DC

	Gdiplus::GdiplusStartup(&gdiPlusToken, &gsi, nullptr);
	this->graphics = Gdiplus::Graphics::FromHDC(BackBufferDC);

	TerrainObject* terrainObject = new TerrainObject(graphics);
	std::wstring mapName = L"Stage" + std::to_wstring(g_GameManager.GetStageNumber());

	terrainObject->LoadMapData(mapName);
	gameObjectList.push_back(terrainObject);
	for (auto ground : terrainObject->groundList)
	{
		gameObjectList.push_back(ground);
	}
	for (auto obj : terrainObject->objectList)
	{
		gameObjectList.push_back(obj);
	}

	// object setup
	scenePlayer = new Player(graphics);
	GameObject* player = scenePlayer;
	player->transform->SetTransform(terrainObject->spawnPosition);
	gameObjectList.push_back(player);

	g_GameManager.Initialize(graphics);
}

void PlayScene::PhysicsUpdate()
{
	// NOTE - enter 다음 바로 exit 호출됨
	// 충돌 저장이 제대로 안됨
	// current는 현재 프레임에서 충돌되어있는 페어 데이터가 있어야하고
	// prev는 current의 데이터를 받아서 exit확인하기

	if (g_GameManager.gameState != GameState::Playing) return;

	currentCollisions.clear();

	for (int i = 0; i < gameObjectList.size(); i++)
	{
		for (int j = 0; j < gameObjectList.size(); j++)
		{
			if (i == j) continue;

			GameObject* objA = gameObjectList[i];
			GameObject* objB = gameObjectList[j];

			if (objA == nullptr || objB == nullptr) continue;
			if (objA->shouldBeDeleted || objB->shouldBeDeleted) continue; // 제거 될 오브젝트 무시

			Collider* colliderA = objA->GetComponent<Collider>();
			Collider* colliderB = objB->GetComponent<Collider>();

			if (colliderA == nullptr || colliderB == nullptr) continue; // 콜라이더 없음

			if (colliderA->IsOverlap(colliderA, colliderB)) // a->b
			{
				auto pair = std::minmax(objA, objB); // 순서 무시
				currentCollisions.insert(pair);

				// 충돌 여부에 따른 함수 호출
				if (previousCollisions.find(pair) == previousCollisions.end())
				{
					// 이전 충돌에 없었으면 enter
					objA->OnColliderEnter(objB);
					objB->OnColliderEnter(objA);
				}
				else
				{
					// 이전에도 충돌이 있었으면 stay
					objA->OnColliderStay(objB);
					objB->OnColliderStay(objA);
				}
			}
		}
	}

	// exit
	for (auto pair : previousCollisions)
	{
		if (currentCollisions.find(pair) == currentCollisions.end())
		{
			GameObject* objA = pair.first;
			GameObject* objB = pair.second;

			if (objA->shouldBeDeleted || objB->shouldBeDeleted) continue; // 제거 될 오브젝트 무시

			objA->OnColliderExit(objB);
			objB->OnColliderExit(objA);
		}
	}

	// 다음 프레임을 위해 이전 충돌 목록 갱신
	previousCollisions = currentCollisions;
}

void PlayScene::Update()
{
	if (g_Input.IsKeyPressed('R'))
	{
		g_SceneManager.ChangeScene(1);
		g_GameManager.gameState = GameState::Ready;
	}

	if (g_GameManager.gameState == GameState::Ready)
	{
		if (g_Input.IsKeyPressed(VK_SPACE))
		{
			g_GameManager.StartCurrentScene();
		}
	}
	if (g_GameManager.gameState == GameState::Playing)
	{
		CheckObjects();

		for (GameObject* obj : gameObjectList)
		{
			if (obj == nullptr) continue;
			obj->Update();
		}

		DeleteDeactiveObjects();
	}
	if (g_GameManager.gameState == GameState::End)
	{
		if (g_Input.IsKeyPressed(VK_SPACE))
		{
			if (scenePlayer->GetHp() > 0) g_GameManager.IncreaseStageNumber();


			if (g_GameManager.GetStageNumber() > g_GameManager.GetMaxStageNumber())
			{
				g_SceneManager.ChangeScene(2);
			}
			else
			{
				g_SceneManager.ChangeScene(1);
			}
			g_GameManager.gameState = GameState::Ready;
		}
	}
}

void PlayScene::Render()
{
	if (g_GameManager.gameState != GameState::End)
	{
		for (GameObject* obj : gameObjectList)
		{
			if (obj == nullptr) continue;

			obj->Render();
		}
	}

	if (g_GameManager.gameState == GameState::End)
	{
		if (scenePlayer->GetHp() <= 0)
		{
			g_GameManager.ShowResultAtScene(false);
		}
		else
		{
			g_GameManager.ShowResultAtScene(true);
		}
	}
}