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

	template<typename T>
	T* GetComponent();

	template<typename T> 
	void AddComponet(T* comp);

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
inline void GameObject::AddComponet(T* comp)
{	
	componentList.push_back(comp);
}
