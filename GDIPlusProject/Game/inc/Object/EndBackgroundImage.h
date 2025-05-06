#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"

class EndBackgroundImage : public GameObject
{
public:
	EndBackgroundImage(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~EndBackgroundImage();
	void Initialize() override;

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer;
};

