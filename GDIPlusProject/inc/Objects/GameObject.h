#pragma once
#include "Manager/UtilityManager.h"
#include "Manager/GDIPlusManager.h"
#include "Component/Component.h"
#include "Component/Transform.h"

#include <string.h>
#include <vector>

class GameObject
{
public:
	GameObject();
	GameObject(float width, float height);
	virtual ~GameObject();

	void SetDefault();
	void SetName(wchar_t* targetName);
	void GetName(wchar_t** bufferPtr);

	virtual void Initialize();
	virtual void Update();
	virtual void Render(Gdiplus::Graphics* graphics);

	// Event
	virtual void OnColliderOverlap(GameObject* other);
	virtual void OnColliderExit(GameObject* other);

	// Component function
	template<typename T>
	T* GetComponent();

	template<typename T>
	std::vector<T*> Getcomponents();

	template<typename T> 
	T* AddComponent();

	// Elements
	wchar_t* name;	
	Transform* transform;

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
	componentList.push_back(comp); // 엑세스 위험

	return comp;
}
