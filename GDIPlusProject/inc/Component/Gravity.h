#pragma once
#include "Manager/SettingManager.h"
#include "Component/Component.h"
#include "Objects/GameObject.h"

class Gravity : Component
{
public:
	Gravity();
	~Gravity();

	void Initialize(GameObject* objectPtr);
	void Update(); // 중력 업데이트

	float GetFallingSpeed();
	void SetIsGround(bool value);
	bool GetIsGround();

private:
	GameObject* owner;	// 중력에 영향 받는 오브젝트
	float ownerHeight;	// 임시
	float fallingSpeed; // 낙하 속도
	bool isGround;		// 땅인지 확인하는 bool값
};

// 해당 위치가 땅인지 확인하기 -> 어떻게?