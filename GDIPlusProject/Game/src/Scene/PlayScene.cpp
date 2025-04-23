#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Manager/SceneManager.h"

#include "Scene/PlayScene.h"
#include "Component/Collider.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/Map/Stage1.h"
#include "Manager/ScoreManager.h"
#include "Manager/TextManager.h"

void PlayScene::Enter(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	this->hwnd = hwnd;
	this->FrontBufferDC = frontBufferDC;	// 앞면 DC
	this->BackBufferDC = backBufferDC;	// 뒷면 DC

	Gdiplus::GdiplusStartup(&gdiPlusToken, &gsi, nullptr);
	this->graphics = Gdiplus::Graphics::FromHDC(BackBufferDC);

	gameObjectList.push_back(new Player(graphics));

	Stage1* stage1 = new Stage1(graphics);
	int groundCount = stage1->groundList.size();
	for (int i = 0; i < groundCount; i++)
	{
		gameObjectList.push_back(stage1->groundList[i]);
	}

	g_TextManager.Initialize(this->graphics);

	g_ScoreManager.ResetData();
	sceneTimer = 0;
}

void PlayScene::PhysicsUpdate()
{
	currentCollisions.clear();

	for (int i = 0; i < gameObjectList.size(); i++)
	{
		for (int j = i + 1; j < gameObjectList.size(); j++)
		{
			GameObject* objA = gameObjectList[i];
			GameObject* objB = gameObjectList[j];
			Collider* colliderA = objA->GetComponent<Collider>();
			Collider* colliderB = objB->GetComponent<Collider>();

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
	for (const auto& pair : previousCollisions)
	{
		if (currentCollisions.find(pair) == currentCollisions.end())
		{
			GameObject* objA = pair.first;
			GameObject* objB = pair.second;
			objA->OnColliderExit(objB);
			objB->OnColliderExit(objA);
		}
	}

	// 다음 프레임을 위해 이전 충돌 목록 갱신
	previousCollisions = currentCollisions;
}

void PlayScene::Update()
{
	//sceneTimer += g_GameTime.GetDeltaTime();
	CheckObjects();

	//if (sceneTimer > sceneMaxTimer) return;

	for (GameObject* obj : gameObjectList)
	{
		obj->Update();
	}
}

void PlayScene::Render()
{
	//if (sceneTimer > sceneMaxTimer)
	//{
	//	g_SceneManager.ChangeScene(2);
	//}

	for (GameObject* obj : gameObjectList)
	{
		obj->Render();
	}
}