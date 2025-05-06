#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"

class TextManager
{
public:	
	TextManager() = default;
	~TextManager() = default;

	void Initialize(Gdiplus::Graphics* g);
	void DrawTextByViewport(const wchar_t* textBuffer, float x, float y);
	void DrawTextByViewport(const std::wstring& text, float x, float y);
protected:
	Gdiplus::Graphics* graphics;
};

extern TextManager g_TextManager;