#include "Scenes/MenuScene.h"

MenuScene::MenuScene()
{
	g_hwnd = {};
	g_FrontBufferDC = {};    // 앞면 DC
	g_BackBufferDC = {};    // 뒷면 DC
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
	//SpriteCollider* playerCollider = player->GetComponent<SpriteCollider>();
	//testObj->OnColliderOverlap(playerCollider); // -> 이게 오브젝트 스크립트 내부에서 일어나야함, 즉 업데이트에서 일어나야함 ? 그럼 해당 함수는?
	for (GameObject* objA : gameObjectList)
	{
		for (GameObject* objB : gameObjectList)
		{
			if (objA == objB) continue;
			
			SpriteCollider* colliderA = objA->GetComponent<SpriteCollider>();
			SpriteCollider* colliderB = objB->GetComponent<SpriteCollider>();

			if (colliderA == nullptr || colliderB == nullptr) continue;			

			if (colliderA->IsOverlap(colliderA, colliderB)) // a->b
			{
				objA->OnColliderOverlap(objB);
				printf("a->b 충돌\n");
			}
		}
	}
}

void MenuScene::Update()
{
	//testObj->Update();
	//player->Update();
	for (GameObject* obj : gameObjectList)
	{
		obj->Update();
	}
}

void MenuScene::Render()
{
	//testObj->Render(g_pBackBufferGraphics);
	//player->Render(g_pBackBufferGraphics);
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