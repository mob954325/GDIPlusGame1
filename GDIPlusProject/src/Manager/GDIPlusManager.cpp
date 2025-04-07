#include "Manager/GDIPlusManager.h"

ULONG_PTR GDIPlusManager::g_GdiPlusToken = 0;
Gdiplus::GdiplusStartupInput GDIPlusManager::gsi = {};
bool GDIPlusManager::initialized = false;

void GDIPlusManager::Initialize()
{
	if (!initialized)
	{
		Gdiplus::GdiplusStartup(&g_GdiPlusToken, &gsi, nullptr);
		initialized = true;
	}
}

void GDIPlusManager::ShutDown()
{
	if (initialized)
	{
		Gdiplus::GdiplusShutdown(g_GdiPlusToken);
		initialized = false;
	}
}
