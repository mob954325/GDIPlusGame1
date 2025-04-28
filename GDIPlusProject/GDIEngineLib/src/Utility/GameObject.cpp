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



	// printf("GameObject 소멸자 호출");
}

void GameObject::Initialize()
{
	// 초기화
}

void GameObject::Update()
{
	// 업데이트
	if (shouldBeDeleted) return;
	
	UpdateImpl();
	UpdateComponents();
}

void GameObject::Render()
{
	// 랜더링 내용
	if (shouldBeDeleted) return;

	RenderImpl();
	RenderComponents();
}

void GameObject::UpdateImpl()
{
	// 업데이트 구현 내용
}

void GameObject::RenderImpl()
{
	// 업데이트 랜더 내용
}

void GameObject::OnColliderEnter(GameObject* other)
{
	// 충돌 내용
	if (shouldBeDeleted) return;
	if (other->shouldBeDeleted) return;

	OnColliderEnterImpl(other);
}

void GameObject::OnColliderStay(GameObject* other)
{
	// 충돌 중일 때 내용
	if (shouldBeDeleted) return;
	if (other->shouldBeDeleted) return;

	OnColliderStayImpl(other);
}

void GameObject::OnColliderExit(GameObject* other)
{
	// 충돌 안 할 때 실행
	if (shouldBeDeleted) return;
	if (other->shouldBeDeleted) return;

	OnColliderExitImpl(other);
}

void GameObject::OnColliderEnterImpl(GameObject* other)
{
	// OnColliderEnter 내용 구현
}

void GameObject::OnColliderStayImpl(GameObject* other)
{
	// OnColliderStay 내용 구현
}

void GameObject::OnColliderExitImpl(GameObject* other)
{
	// OnColliderExit 내용 구현
}

void GameObject::UpdateComponents()
{
	for (Component* comp : componentList)
	{
		comp->Update();
	}
}

void GameObject::RenderComponents()
{
	for (Component* comp : componentList)
	{
		comp->Render();
	}
}
