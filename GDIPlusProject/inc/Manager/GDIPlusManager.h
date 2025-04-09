#pragma once
#include <stdio.h>
#include <windows.h>

#include "gdiplus.h"
#pragma comment(lib, "gdiplus.lib")

class GDIPlusManager
{
public:
	static void Initialize();
	static void ShutDown();

	static ULONG_PTR s_GdiPlusToken;
	static Gdiplus::GdiplusStartupInput s_gsi;
	static bool s_initialized;
};

