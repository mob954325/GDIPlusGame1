#pragma once
#include "Manager/UtilityManager.h"

class GameObject;

// 컴포넌트의 베이스 클래스
class Component
{
public:	
	Component();
	Component(GameObject* obj) : owner(obj) { };
	virtual ~Component();

	GameObject* owner;
};

