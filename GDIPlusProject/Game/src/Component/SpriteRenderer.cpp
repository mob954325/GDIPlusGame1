#include "Component/SpriteRenderer.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"

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
	animationGameTimer += g_GameTime.GetDeltaTime();
	if (animationGameTimer > maxAnimationGameTime)
	{
		animationGameTimer = 0.0f;

		currFrame++;
		currFrame %= imageFrameCount;
	}
}

void SpriteRenderer::Render()
{
	if (isActive)
	{
		for (int y = 0; y < owner->transform->height / imageHeight; y++)
		{
			for (int x = 0; x < owner->transform->width / imageWidth; x++)
			{
				DrawImage(x, y);
			}
		}
	}
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

void SpriteRenderer::DrawImage(int gridX, int gridY)
{
	if (imageBitMap == nullptr) return;

	//assert(graphics != nullptr && "SpriteRenderer's GDIPlus::Graphics is nullptr");
	Gdiplus::Rect srcRect(imageWidth * currFrame, 0, imageWidth, imageHeight);	// 소스의 영역
	Gdiplus::Rect destRect((int)owner->transform->position.x + (gridX * imageWidth), (int)owner->transform->position.y + (gridY * imageHeight), srcRect.Width, srcRect.Height);			// 화면에 그릴 영역
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel); // 소스의 일부분만을 그린다.
}

void SpriteRenderer::GetImageInfo(const wchar_t* infoName, const wchar_t* path)
{
	FILE* file = nullptr;
	_wfopen_s(&file, path, L"r");

	if (!file)
		return;

	wchar_t buffer[1024];
	wchar_t* nextbuffer = nullptr;
	wchar_t* bufferToken = nullptr;
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

						if (bufferToken)
						{
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
					break;
				}

			} while (fgetws(buffer, 1024, file));
		} // if getws

		fclose(file);
	}
}
