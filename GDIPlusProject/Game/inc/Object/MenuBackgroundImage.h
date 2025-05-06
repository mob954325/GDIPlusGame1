#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"

class MenuBackgroundImage : public GameObject
{
public:
	MenuBackgroundImage(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~MenuBackgroundImage();
	void Initialize() override;

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer;
};

