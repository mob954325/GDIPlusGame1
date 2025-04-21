#pragma once
class GameObject; // 상호 참조를 위한 전방선언

// 컴포넌트의 베이스 클래스
class Component
{
public:
	Component();
	Component(GameObject* obj) : owner(obj) {};
	virtual ~Component();

	GameObject* owner;
};
