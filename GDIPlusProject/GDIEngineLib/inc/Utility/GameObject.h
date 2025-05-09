﻿#pragma once
#include "Component.h"
#include "Transform.h"
#include "Monobehaviour.h"

#include <string.h>
#include <vector>

class GameObject : public Monobehaviour
{
public:
	GameObject();
	virtual ~GameObject();

	void Initialize() override;
	void Update() override;
	void Render() override;

	virtual void UpdateImpl();
	virtual void RenderImpl();

	// Event
	void OnColliderEnter(GameObject* other);
	void OnColliderStay(GameObject* other);
	void OnColliderExit(GameObject* other);

	virtual void OnColliderEnterImpl(GameObject* other);
	virtual void OnColliderStayImpl(GameObject* other);
	virtual void OnColliderExitImpl(GameObject* other);

	// Component function
	template<typename T>
	T* GetComponent();

	template<typename T>
	std::vector<T*> Getcomponents();

	template<typename T>
	T* AddComponent();

	// Elements
	Transform* transform = {};
	bool shouldBeDeleted = false;	// 삭제 예정인지 확인하는 변수

private:
	void UpdateComponents();
	void RenderComponents();
	std::vector<Component*> componentList;
};

template<typename T>
inline T* GameObject::GetComponent()
{
	for (Component* comp : componentList)
	{
		if (T* casted = dynamic_cast<T*>(comp)) // 실패 시 0 반환 (throw 반환 안함)
		{
			return casted;
		}
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> GameObject::Getcomponents()
{
	std::vector<T*> tempList;
	tempList.reserve(componentList.size());

	for (Component* comp : componentList)
	{
		if (T* casted = dynamic_cast<T*>(comp))
		{
			tempList.push_back(casted);
		}
	}

	return tempList;
}

template<typename T>
inline T* GameObject::AddComponent()
{
	T* comp = new T(this);
	componentList.push_back(comp);

	return comp;
}
