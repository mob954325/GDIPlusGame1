#pragma once
#include "framework.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/Collider.h"
#include "Component/SpriteRenderer.h"

class Spike : public GameObject
{	
public:
	Spike(Gdiplus::Graphics* g) : graphics(g) { Initialize(); }
	~Spike();
	void Initialize() override;

protected:
	Gdiplus::Graphics* graphics = nullptr;
	SpriteRenderer* spriteRenderer;
	Collider* collider = nullptr;
};

