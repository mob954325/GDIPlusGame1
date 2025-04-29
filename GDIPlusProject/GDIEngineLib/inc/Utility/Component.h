#pragma once
#include "Monobehaviour.h"
class GameObject; // 상호 참조를 위한 전방선언

// 컴포넌트의 베이스 클래스
class Component : public Monobehaviour
{
public:
	Component();
	Component(GameObject* obj) : owner(obj) {};
	virtual ~Component();

	void Initialize() override;
	void Update() override;
	void Render() override;

	void SetActive(bool value);
	GameObject* owner;

protected:
	bool isActive = true;
};