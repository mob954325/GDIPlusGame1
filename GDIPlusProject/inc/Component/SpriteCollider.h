#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"

// 스프라이트 크기로 Colilder 크기를 지정하는 함수
class SpriteCollider
{
public:
#if _DEBUG
	void RenderCollider(Gdiplus::Graphics* graphics);
#endif

	SpriteCollider();
	~SpriteCollider();

	// 값 갱신 함수
	void UpdateValue(GameObject object, SpriteRenderer spriteRenderer);
	// AABB 충돌 검사 함수
	bool IsOverlap(SpriteCollider objectA, SpriteCollider objectB);
	SpriteCollider* GetColliderComponent();

	float minX; float maxX;	// 기준은 좌측 상단을 (0,0)으로 함
	float minY; float maxY;
};

/// 각 mim max 위치 
/// (minX, minY) ----- (maxX, minY)
///				 |   |
///				 |   |
///				 |   |
///	(minX, maxY) ----- (maxX, maxY)
///