#include "Objects/GameObject.h"

GameObject::GameObject()
{
	name = NULL;
	transform = new Transform();
	AddComponet(transform);
}

GameObject::GameObject(float width, float height)
{
	name = NULL;
	transform = new Transform(transform->position, width, height);
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
	else
	{
		printf("GameObject 소멸자 호출");
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

void GameObject::Initialize()
{
	// 초기화
}

void GameObject::Update()
{
	// 업데이트
}

void GameObject::Render(Gdiplus::Graphics* graphics)
{
	// 랜더링 내용
}

void GameObject::OnColliderOverlap(GameObject* other)
{
	// 충돌 내용
}