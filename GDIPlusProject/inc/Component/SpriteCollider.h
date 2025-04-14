#pragma once
#include "Component/Component.h"
#include "Objects/GameObject.h"
#include "SpriteRenderer.h"

// 스프라이트 크기로 Colilder 크기를 지정하는 함수
class SpriteCollider : public Component
{
public:
	SpriteCollider();
	~SpriteCollider();
	
	void UpdateValue(GameObject* object, SpriteRenderer* spriteRenderer); // 값 갱신 함수	
	bool IsOverlap(SpriteCollider* objectA, SpriteCollider* objectB); // AABB 충돌 검사 함수

	// Debug
	void RenderCollider(Gdiplus::Graphics* graphics);

	RECT bound;
};

/// 각 Rect별 위치 
/// (Left, Bottom) ----- (Right, Bottom)
///				   |   |
///				   |   |
///				   |   |
///	   (Left, Top) ----- (Right, Top)
///