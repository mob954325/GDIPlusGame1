#include "framework.h"
#include "Manager/TextManager.h"

TextManager g_TextManager;

void TextManager::Initialize(Gdiplus::Graphics* g)
{
	graphics = g;
}

void TextManager::DrawTextByViewport(const wchar_t* textBuffer,float x, float y)
{
	if (graphics == nullptr)
	{
		OutputDebugString(L"TextManager -> graphic == nullptr\n");
	}

	Gdiplus::FontFamily  fontFamily(L"Times New Roman");
	Gdiplus::Font        font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointF(0, 0);
	Gdiplus::SolidBrush  solidBrush(Gdiplus::Color(255, 255, 255, 255));	

	// 텍스트 크기 받기
	Gdiplus::RectF textRect;
	graphics->MeasureString(textBuffer, -1, &font, pointF, nullptr, &textRect);

	float gapX = textRect.Width / 2.0f;
	float gapXRatio = gapX / g_WindowConfig.windowWidth;
	pointF.X = (g_WindowConfig.windowWidth * (x - gapXRatio));
	pointF.Y = g_WindowConfig.windowHeight * y;

	// 출력
	graphics->DrawString(textBuffer, -1, &font, pointF, &solidBrush);
}
