#include "Objects/GameObject.h"

GameObject::GameObject()
{
	name = NULL;
	transform = new Transform();
	AddComponet(transform);
}

GameObject::~GameObject()
{
	// 컴포넌트 제거
	int componentCount = (int)componentList.size();
	for (int i = 0; i < componentCount; i++)
	{
		delete componentList[i];
	}

	if (name != NULL)
	{
		printf("%ws GameObject 소멸자 호출", name);
		free(name);
	}
}

void GameObject::SetDefault()
{
	transform->SetTransform(0.0f, 0.0f);
}

void GameObject::SetName(wchar_t* targetName)
{
	int targetNameLength = (int)wcslen(targetName);
	name = (wchar_t*)malloc((targetNameLength + 1) * sizeof(wchar_t));
	name = targetName;
}

void GameObject::GetName(wchar_t** bufferPtr)
{
	*bufferPtr = name;
}
