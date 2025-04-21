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
	for (GameObject* objA : gameObjectList)
	{
		for (GameObject* objB : gameObjectList)
		{
			if (objA == objB) continue;

			Collider* colliderA = objA->GetComponent<Collider>();
			Collider* colliderB = objB->GetComponent<Collider>();

			bool isOverlap = false;
			if (colliderA->IsOverlap(colliderA, colliderB)) // a->b
			{
				isOverlap = true;
			}

			// 충돌 여부에 따른 함수 호출
			if (isOverlap)
			{
				objA->OnColliderOverlap(objB);
			}
			else
			{
				objA->OnColliderExit(objB);
			}
		}
	}
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