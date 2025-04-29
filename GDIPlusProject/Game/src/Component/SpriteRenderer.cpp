#include "Component/SpriteRenderer.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"

SpriteRenderer::~SpriteRenderer()
{
	if (imageBitMap != nullptr)
	{
		std::cout << "Deleting bitmap at address: " << imageBitMap << std::endl; // 메모리 주소 출력
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
		for (int y = 0; y < owner->transform->height / drawHeight; y++)
		{
			for (int x = 0; x < owner->transform->width / drawWidth; x++)
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
	sourceWidth = imageBitMap->GetWidth();
	sourceHeight = imageBitMap->GetHeight();
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

	Gdiplus::Rect srcRect(drawWidth * currFrame, 0, drawWidth, drawHeight);	// 소스의 영역
	Gdiplus::Rect destRect((int)owner->transform->position.x + (gridX * drawWidth), (int)owner->transform->position.y + (gridY * drawHeight), srcRect.Width, srcRect.Height);			// 화면에 그릴 영역
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel); // 소스의 일부분만을 그린다.
}

void SpriteRenderer::DrawImage(int gridX, int gridY, int tileNum)
{
	if (imageBitMap == nullptr) return;

	int tilesPerRow = sourceWidth / drawWidth;		// 가로 개수
	int tilesPerCol = sourceHeight / drawHeight;	// 세로 개수

	if (tileNum < 0 || tileNum >= tilesPerRow * tilesPerCol) return; // 존재하지 않는 위치

	int y = tileNum / tilesPerRow;
	int x = tileNum % tilesPerRow;


	Gdiplus::Rect srcRect(drawWidth * x, drawHeight * y, drawWidth, drawHeight);
	Gdiplus::Rect destRect(
		(int)owner->transform->position.x + (gridX * drawWidth), 
		(int)owner->transform->position.y + (gridY * drawHeight), 
		srcRect.Width, srcRect.Height
	);
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);

	std::cout << "tileNum: " << tileNum << " -> srcX: " << srcRect.X << ", srcY: " << srcRect.Y << std::endl;
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
								drawWidth = _wtoi(bufferToken);
								drawHeight = drawWidth;
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
