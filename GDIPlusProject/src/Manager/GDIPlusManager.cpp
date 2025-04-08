#include "Manager/GDIPlusManager.h"

ULONG_PTR GDIPlusManager::s_GdiPlusToken = 0;
Gdiplus::GdiplusStartupInput GDIPlusManager::s_gsi = {};
bool GDIPlusManager::s_initialized = false;

void GDIPlusManager::Initialize()
{
	if (!s_initialized)
	{
		Gdiplus::GdiplusStartup(&s_GdiPlusToken, &s_gsi, nullptr);
		s_initialized = true;
	}
}

void GDIPlusManager::ShutDown()
{
	if (s_initialized)
	{
		Gdiplus::GdiplusShutdown(s_GdiPlusToken);
		s_initialized = false;
	}
}
