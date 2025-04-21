#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/Component.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* obj) : Component(obj),
		imageBitMap(nullptr), currFrame(0), imageFrameCount(0), imageWidth(0), imageHeight(0) {
	};
	~SpriteRenderer();
	bool GetImage(const wchar_t* path);
	void DrawImage(Gdiplus::Graphics* graphics, int posX, int posY);
	void GetImageInfo(const wchar_t* infoName, const wchar_t* path); // 임시 부정확한 이름

	int currFrame;					// 현재 이미지 프레임 (GetImage에서 초기화)
	int imageFrameCount;			// 이미지 프레임 개수
	int imageWidth;					// 각 이미지 넓이
	int imageHeight;				// 이미지 높이

protected:
	Gdiplus::Bitmap* imageBitMap;	// 이미지 비트맵
};
