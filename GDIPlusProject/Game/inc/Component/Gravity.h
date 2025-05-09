﻿#pragma once
#include "GDIEngineLib/inc/Utility/Vector2.h"
#include "GDIEngineLib/inc/Utility/Component.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "Component/SpriteRenderer.h"
#include <math.h>

class Gravity : public Component
{
public:
	Gravity();
	Gravity(GameObject* obj) : Component(obj) { };
	~Gravity();

	void Initialize() override;
	void Update() override;
	void Render() override;

	Vector2 GetVelocity();
	void ApplyForce(Vector2 forceVec);
	void SetVelocityZero();
	void SetVelocityYZero();
	void SetVelocityXZero();
	void SetIsGround(bool value);
	bool GetIsGround();

private:
	void ApplyFrictionForce();
	void ApplyGravity();
	void ClampVelocity();

	Vector2 velocity = Vector2(0.0f, 0.0f);

	float maxVelocityY = 1000.0f;
	float maxVelocityX = 250.0f;

	float fallingSpeed = 1000.0f;	// 낙하 속도
	float frictionForce = 600.0f;	// 마찰력 -> 높을 수록 빨리 멈춤

	bool isGround = false;		// 땅인지 확인하는 bool값
};