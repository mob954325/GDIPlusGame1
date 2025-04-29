#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/Component.h"

// NOTE: 랜더링 하기 전 반드시 GetGraphic으로 Graphics의 주소를 받을 것

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* obj) : Component(obj) { };
	~SpriteRenderer();

	void Initialize() override;
	void Update() override;
	void Render() override;

	bool GetImage(const wchar_t* path);
	void GetGraphic(Gdiplus::Graphics** graphicsPtr);
	void DrawImage(Gdiplus::Graphics* graphics, int posX, int posY);
	void DrawImage();
	void GetImageInfo(const wchar_t* infoName, const wchar_t* path);

	int currFrame = 0;					// 현재 이미지 프레임 (GetImage에서 초기화)
	int imageFrameCount = 0;			// 이미지 프레임 개수
	int imageWidth = 0;					// 각 이미지 넓이
	int imageHeight = 0;				// 이미지 높이

protected:
	Gdiplus::Bitmap* imageBitMap = {};	// 이미지 비트맵
	Gdiplus::Graphics* graphics = {};
};
