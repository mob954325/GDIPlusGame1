#pragma once
#include "Manager/UtilityManager.h"

class GameObject;

// 컴포넌트의 베이스 클래스
class Component
{
public:	
	virtual ~Component();

	GameObject* owner;
	void SetOwner(GameObject* object);
};

