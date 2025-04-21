#include "App/Game.h"
#include "App/GameApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameApp app;

    app.Initialize();

#if _DEBUG
    app.InitConsole();
#endif

    app.Run();
    app.Shutdown();

#if _DEBUG
    app.ShutdownConsole();
#endif

    return (int)1;
}