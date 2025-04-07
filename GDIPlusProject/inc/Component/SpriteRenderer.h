#pragma once

#include <stdio.h>
#include <windows.h>

#include "Manager/GDIPlusManager.h"

class SpriteRenderer
{
public:
	bool GetImage(const wchar_t* path);
	void DrawImage(Gdiplus::Graphics* graphics, int posX, int posY);
	void DeleteImage();
	void GetImageInfo(const wchar_t* infoName, const wchar_t* path);

	int currFrame;					// ���� �̹��� ������ (GetImage���� �ʱ�ȭ)
	int imageFrameCount;			// �̹��� ������ ����
	int imageWidth;					// �� �̹��� ����
	int imageHeight;
protected:
	Gdiplus::Bitmap* imageBitMap;	// �̹��� ��Ʈ��
};

