#pragma once
#include "Component.h"
#include "Transform.h"

#include <string.h>
#include <vector>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();

	// Event
	virtual void OnColliderEnter(GameObject* other);
	virtual void OnColliderStay(GameObject* other);
	virtual void OnColliderExit(GameObject* other);

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
