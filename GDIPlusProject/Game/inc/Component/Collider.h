#pragma once
#include "GDIEngineLib/inc/Utility/Component.h"
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include <windows.h>

// 스프라이트 크기로 Colilder 크기를 지정하는 함수
class Collider : public Component
{
public:
	Collider();
	Collider(GameObject* obj) : Component(obj), bound({}) {};
	~Collider();

	void UpdateValue(GameObject* object); // 값 갱신 함수	
	bool IsOverlap(Collider* objectA, Collider* objectB); // AABB 충돌 검사 함수

	RECT bound;
};

/// 각 Rect별 위치 
/// (Left, Bottom) ----- (Right, Bottom)
///				   |   |
///				   |   |
///				   |   |
///	   (Left, Top) ----- (Right, Top)
///

