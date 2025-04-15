#include "Scenes/MenuScene.h"

MenuScene::MenuScene()
{
	g_hwnd = {};
	g_FrontBufferDC = {};	// 앞면 DC
	g_BackBufferDC = {};	// 뒷면 DC
	g_pBackBufferGraphics = {};

	gameObjectList = {};
}

MenuScene::~MenuScene()
{
	delete g_pBackBufferGraphics;
}

void MenuScene::Initialize(HWND hwnd, HDC frontBufferDC, HDC backBufferDC)
{
	g_hwnd = hwnd;
	g_FrontBufferDC = frontBufferDC;
	g_BackBufferDC = backBufferDC;

	g_pBackBufferGraphics = Gdiplus::Graphics::FromHDC(g_BackBufferDC);

	gameObjectList.push_back(new BackGroundObject());
	gameObjectList.push_back(new TestTerrainObject());
	gameObjectList.push_back(new TestObject(200, 200));
	gameObjectList.push_back(new Player());

	for (GameObject* obj : gameObjectList)
	{
		obj->Initialize();
	}
}

void MenuScene::PhysicsUpdate()
{
	for (GameObject* objA : gameObjectList)
	{
		for (GameObject* objB : gameObjectList)
		{
			if (objA == objB) continue;
			
			std::vector<SpriteCollider*> colliderAList = objA->Getcomponents<SpriteCollider>();
			std::vector<SpriteCollider*> colliderBList = objB->Getcomponents<SpriteCollider>();

			if (colliderAList.size() == 0 || colliderBList.size() == 0) continue;

			bool isOverlap = false;
			// 오브젝트에 있는 모든 콜라이더 검사
			for (SpriteCollider* colliderA : colliderAList)
			{
				for (SpriteCollider* colliderB : colliderBList)
				{
					if (colliderA->IsOverlap(colliderA, colliderB)) // a->b
					{
						isOverlap = true;
						break;
					}
				}
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

void MenuScene::Update()
{
	for (GameObject* obj : gameObjectList)
	{
		obj->Update();
	}
}

void MenuScene::Render()
{
	for (GameObject* obj : gameObjectList)
	{
		obj->Render(g_pBackBufferGraphics);
	}
}

void MenuScene::Uninitialize()
{
}

// 안쓰는 함수
//void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap);
//void CheckFileLoad(HWND hwnd, Gdiplus::Bitmap* bitmap)
//{
//	if (bitmap->GetLastStatus() != Gdiplus::Ok)
//	{
//		MessageBox(hwnd, L"PNG 파일 로드 실패", L"오류", MB_ICONERROR);
//		PostQuitMessage(0);
//	}
//}