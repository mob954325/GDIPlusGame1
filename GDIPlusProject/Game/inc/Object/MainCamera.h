#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "GDIEngineLib/inc//Utility/Vector2.h"

class MainCamera : public GameObject
{
public:
	void Initialize() override;
	void UpdateImpl() override;
	void RenderImpl() override;

	Vector2 moveVec = Vector2();
	Vector2 InvertTransformPosition();
	bool isMoved = false;
private:
	GameObject* target; // 카메라가 보는 타켓 오브젝트

	float speed = 20.0f;
};

