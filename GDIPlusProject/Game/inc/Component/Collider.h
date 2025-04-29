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

	void Initialize() override;
	void Update() override;
	void Render() override;
	bool IsOverlap(Collider* objectA, Collider* objectB); // AABB 충돌 검사 함수

	RECT bound; // left, top, right, bottom
private:
};

/// 각 Rect별 위치 
/// (Left, Bottom) ----- (Right, Bottom)
///				   |   |
///				   |   |
///				   |   |
///	   (Left, Top) ----- (Right, Top)
///

