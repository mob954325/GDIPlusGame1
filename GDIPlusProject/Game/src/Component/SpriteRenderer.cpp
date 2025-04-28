#include "Component/SpriteRenderer.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include <assert.h>

SpriteRenderer::~SpriteRenderer()
{
	if (imageBitMap != nullptr)
	{
		delete imageBitMap;
		imageBitMap = nullptr;
	}
}

void SpriteRenderer::Initialize()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::Render()
{
	DrawImage();
}

bool SpriteRenderer::GetImage(const wchar_t* path)
{
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(path);

	// 파일 로드 확인
	if (bitmap->GetLastStatus() != Gdiplus::Ok)
	{
		delete bitmap; // 로드 실패
		return false;
	}

	imageBitMap = bitmap;
	imageWidth = imageBitMap->GetWidth();
	imageHeight = imageBitMap->GetHeight();
	imageFrameCount = 1;
	currFrame = 0;
	return true;
}

void SpriteRenderer::GetGraphic(Gdiplus::Graphics** graphicsPtr)
{
	graphics = *graphicsPtr;
}

void SpriteRenderer::DrawImage(Gdiplus::Graphics* graphics, int posX, int posY)
{
	Gdiplus::Rect srcRect(imageWidth * currFrame, 0, imageWidth, imageHeight);	// 소스의 영역
	Gdiplus::Rect destRect(posX, posY, srcRect.Width, srcRect.Height);			// 화면에 그릴 영역
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel); // 소스의 일부분만을 그린다.
}

void SpriteRenderer::DrawImage()
{
	//assert(graphics != nullptr && "SpriteRenderer's GDIPlus::Graphics is nullptr");
	Gdiplus::Rect srcRect(imageWidth * currFrame, 0, imageWidth, imageHeight);	// 소스의 영역
	Gdiplus::Rect destRect((int)owner->transform->position.x, (int)owner->transform->position.y, srcRect.Width, srcRect.Height);			// 화면에 그릴 영역
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel); // 소스의 일부분만을 그린다.
}

void SpriteRenderer::GetImageInfo(const wchar_t* infoName, const wchar_t* path)
{
	FILE* file = {};
	_wfopen_s(&file, path, L"r");
	wchar_t buffer[1024];
	wchar_t* nextbuffer = NULL;
	wchar_t* bufferToken = NULL;
	wchar_t seps[] = L",\t\n";

	memset(buffer, 0, 1024);

	// csv에서 이미지 정보 찾기
	if (file)
	{
		if (fgetws(buffer, 1024, file))
		{
			// BOM 무시
			if ((unsigned char)buffer[0] == 0xEF &&
				(unsigned char)buffer[1] == 0xBB &&
				(unsigned char)buffer[2] == 0xBF)
			{
				memmove(buffer, buffer + 3, (wcslen(buffer + 3) + 1) * sizeof(wchar_t));
			}

			// 데이터 찾기
			do
			{
				bufferToken = wcstok_s(buffer, seps, &nextbuffer);
				if (wcscmp(bufferToken, infoName) == 0) // csv에서 찾는 단어가 존재함
				{
					for (int i = 0; i < 2; i++)
					{
						bufferToken = wcstok_s(NULL, seps, &nextbuffer);
						if (i == 0)
						{
							imageWidth = _wtoi(bufferToken);
						}
						else if (i == 1)
						{
							imageFrameCount = _wtoi(bufferToken);
						}
					}
				}

			} while (fgetws(buffer, 1024, file));
		} // if getws
	}
}
