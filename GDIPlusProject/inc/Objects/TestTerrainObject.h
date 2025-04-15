#pragma once
#include "Objects/GameObject.h"
#include "Component/SpriteRenderer.h"
#include "Component/SpriteCollider.h"
#include "Component/Gravity.h"

class TestTerrainObject : public GameObject
{
public:
	TestTerrainObject();
	~TestTerrainObject();

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	void OnColliderOverlap(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;
	SpriteRenderer* tileSprite;
	SpriteCollider* collider;
	SpriteCollider* collider2;

private:
	int tiles[10][10] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1},
	};

	void SetCollider();
};

/// 지형 콜라이더 추가
/// 1. 오브젝트안에 콜라이더를 여러개 만들고 그걸 체크한다
/// -> 오브젝트에는 한개의 이벤트 함수만 있음, bound도 한 개만 있음
/// 2. 오브젝트로 지형 오브젝트를 분리하여 개별로 체크한다.
/// -> 나중에 여러 지형 추가할 때 위치 정하기 힘들거같음