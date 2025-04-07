#include "Component/SpriteRenderer.h"

bool SpriteRenderer::GetImage(const wchar_t* path)
{
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(path);

	// ���� �ε� Ȯ��
	if (bitmap->GetLastStatus() != Gdiplus::Ok)
	{
		delete bitmap; // �ε� ����
		return false;
	}

	imageBitMap = bitmap;
	imageWidth = imageBitMap->GetWidth();
	imageHeight = imageBitMap->GetHeight();
	imageFrameCount = 1;
	currFrame = 0;
	return true;
}

void SpriteRenderer::DrawImage(Gdiplus::Graphics* graphics, int posX, int posY)
{
	Gdiplus::Rect srcRect(imageWidth * currFrame, 0, imageWidth, imageHeight);	// �ҽ��� ����
	Gdiplus::Rect destRect(posX, posY, srcRect.Width, srcRect.Height);			// ȭ�鿡 �׸� ����
	graphics->DrawImage(imageBitMap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel); // �ҽ��� �Ϻκи��� �׸���.
}

void SpriteRenderer::DeleteImage()
{
	delete imageBitMap;
}

void SpriteRenderer::GetImageInfo(const wchar_t* infoName, const wchar_t* path)
{
	FILE* file = {};
	_wfopen_s(&file, path, L"r");
	wchar_t buffer[1024];
	wchar_t* nextbuffer;
	wchar_t* bufferToken;
	wchar_t seps[] = L",\t\n";

	memset(buffer, 0, 1024);

	// csv���� �̹��� ���� ã��
	if (file)
	{
		if (fgetws(buffer, 1024, file))
		{
			// BOM ����
			if ((unsigned char)buffer[0] == 0xEF &&
				(unsigned char)buffer[1] == 0xBB &&
				(unsigned char)buffer[2] == 0xBF)
			{
				memmove(buffer, buffer + 3, (wcslen(buffer + 3) + 1) * sizeof(wchar_t));
			}

			// ������ ã��
			do
			{
				bufferToken = wcstok_s(buffer, seps, &nextbuffer);
				if (wcscmp(bufferToken, infoName) == 0) // csv���� ã�� �ܾ ������
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
