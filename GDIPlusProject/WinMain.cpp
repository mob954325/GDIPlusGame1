#include "WinMain.h"

void Update();
void Render();
void Uninitialize();

// WindowApi, Console
LPCTSTR g_title = TEXT("20250403이성호");
LPCTSTR g_szClassName = TEXT("윈도우 클래스 이름");

int g_width = 1024;
int g_height = 768;

HWND g_hwnd;
HDC g_FrontBufferDC;    // 앞면 DC
HDC g_BackBufferDC;    // 뒷면 DC
HBITMAP g_BackBufferBitmap;

// Scene Control
Scene currentScene = Scene::MENU;
Scene nextScene = Scene::MENU;

// 콘솔 초기화
void InitConsole()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	SetConsoleTitle(L"윈도우 메시지 콘솔 로그");
	printf("콘솔 로그 시작...\n\n");
}

void UninitConsole()
{
	// 표준 출력 스트림 닫기
	fclose(stdout);
	// 콘솔 해제
	FreeConsole();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		Input::IsKeyDown((int)wParam);
		Input::IsKeyPressed((int)wParam);
		Input::IsKeyReleased((int)wParam);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	InitConsole();  // 콘솔 출력 초기화

	// 폴더 경로 콘솔 출력
	char szPath[MAX_PATH] = { 0, };
	GetCurrentDirectoryA(MAX_PATH, szPath);
	printf("Current Directory : %s\n", szPath);

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = g_szClassName;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// 기본 커서 모양
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 기본 아이콘 모양
	RegisterClass(&wc);

	// 원하는 크기가 조정되어 리턴
	RECT rcClient = { 0, 0, (LONG)g_width, (LONG)g_height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		g_szClassName,
		g_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		NULL, NULL, hInstance, NULL);
	g_hwnd = hwnd;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 렌더러 초기화
	Renderer::Initialize(hwnd, g_width, g_height);
	g_FrontBufferDC = Renderer::GetFrontBuffer();
	g_BackBufferDC = Renderer::GetBackBuffer();

	// 나머지 초기화
	GDIPlusManager::Initialize();
	MenuScene::Initialize(hwnd, g_FrontBufferDC, g_BackBufferDC);
	GameTime::InitTime();


	// 게임 루프
	MSG msg = {};
	while (true)
	{
		// 메세지 큐 
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update();
		Render();
	}

	GDIPlusManager::ShutDown();
	Renderer::Uninitialize();
	ReleaseDC(hwnd, g_FrontBufferDC);

	//////////////////////////////////////////////////////////////////////////
	UninitConsole();  // 콘솔 출력 해제
	return (int)msg.wParam;
}

// 루프 함수 ===============================================================================

void Update()
{
	Input::Update();
	GameTime::UpdateTime();

	switch (currentScene)
	{
	case MENU:
		MenuScene::Update();
		break;
	case PLAY:
		break;
	case END:
		break;
	default:
		break;
	}
}

void Render()
{
	Renderer::BeginDraw();

	switch (currentScene)
	{
	case MENU:
		MenuScene::Render();
		break;
	case PLAY:
		break;
	case END:
		break;
	default:
		break;
	}

	Renderer::EndDraw();
}

