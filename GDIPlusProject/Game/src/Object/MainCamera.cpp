#include "Object/MainCamera.h"

#include "GDIEngineLib/inc/Manager/Input.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"

#include "Component/SpriteRenderer.h"

void MainCamera::Initialize()
{
	collider = AddComponent<Collider>();
	collider->bound = { 0,g_WindowConfig.windowHeight, g_WindowConfig.windowWidth, 0 };

	transform->width = g_WindowConfig.windowWidth;
	transform->height = g_WindowConfig.windowHeight;
}

void MainCamera::UpdateImpl()
{
	moveVec = Vector2(0, 0);
	UpdatePositionByTarget();
}

void MainCamera::SetCameraTarget(GameObject* object)
{	
	target = object;
}

void MainCamera::OnColliderEnterImpl(GameObject* other)
{
	SpriteRenderer* sr = other->GetComponent<SpriteRenderer>();
	if (sr != nullptr)
	{
		sr->SetActive(true);
	}
}

void MainCamera::OnColliderStayImpl(GameObject* other)
{
}

void MainCamera::OnColliderExitImpl(GameObject* other)
{
	SpriteRenderer* sr = other->GetComponent<SpriteRenderer>();
	if (sr != nullptr)
	{
		sr->SetActive(false);
	}
}

Vector2 MainCamera::InvertCameraMoveVector()
{
	return Vector2(-moveVec.x, -moveVec.y);
}

void MainCamera::UpdatePositionByTarget()
{
	if (target == nullptr) return;

	// 현재 위치에서 screen width의 절반의 크기보다 target이 벗어나 있으면 벗어난 길이 만큼 이동하기

	Vector2 targetPosition = target->transform->position;
	float gap = targetPosition.x - (transform->position.x + g_WindowConfig.windowWidth * 0.5f);

	if (gap > 0 || gap < 0)
	{
		moveVec.x = gap;
	}}
