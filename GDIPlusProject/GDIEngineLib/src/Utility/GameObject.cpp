#include "pch.h"
#include "Utility/GameObject.h"

GameObject::GameObject()
{
	transform = AddComponent<Transform>();
}

GameObject::~GameObject()
{
	// 컴포넌트 제거
	int componentCount = (int)componentList.size();
	for (int i = 0; i < componentCount; i++)
	{
		delete componentList[i];
	}

	printf("GameObject 소멸자 호출");
}

void GameObject::Initialize()
{
	// 초기화
}

void GameObject::Update()
{
	// 업데이트
	if (shouldBeDeleted) return;
}

void GameObject::Render()
{
	// 랜더링 내용
	if (shouldBeDeleted) return;
}

void GameObject::OnColliderEnter(GameObject* other)
{
	// 충돌 내용
	if (shouldBeDeleted) return;
}

void GameObject::OnColliderStay(GameObject* other)
{
	// 충돌 중일 때 내용
	if (shouldBeDeleted) return;
}

void GameObject::OnColliderExit(GameObject* other)
{
	// 충돌 안 할 때 실행
	if (shouldBeDeleted) return;
}