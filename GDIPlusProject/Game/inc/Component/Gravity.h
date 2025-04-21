#pragma once
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"

class Gravity : public Component
{
public:
	Gravity();
	Gravity(GameObject* obj) : Component(obj), fallingSpeed(550.0f), isGround(false) { };
	~Gravity();

	void Initialize(GameObject* objectPtr);
	void Update(); // 중력 업데이트

	float GetFallingSpeed();
	void SetIsGround(bool value);
	bool GetIsGround();

private:
	float fallingSpeed; // 낙하 속도
	bool isGround;		// 땅인지 확인하는 bool값
};

// 해당 위치가 땅인지 확인하기 -> 어떻게?