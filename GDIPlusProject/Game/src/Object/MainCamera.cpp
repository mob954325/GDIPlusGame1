#include "Object/MainCamera.h"

#include "GDIEngineLib/inc/Manager/Input.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"

void MainCamera::Initialize()
{
}

void MainCamera::UpdateImpl()
{
	moveVec = Vector2();

	if (g_Input.IsKeyDown('S'))
	{
		moveVec = Vector2(0, 1);
	}
	if (g_Input.IsKeyDown('W'))
	{
		moveVec = Vector2(0, -1);
	}
	if (g_Input.IsKeyDown('A'))
	{
		moveVec = Vector2(-1, 0);
	}
	if (g_Input.IsKeyDown('D'))
	{
		moveVec = Vector2(1, 0);
	}

	printf("%f %f\n", moveVec.x, moveVec.y);

	transform->Translate(moveVec * speed * 0.0002f);
}

void MainCamera::RenderImpl()
{
}

Vector2 MainCamera::InvertTransformPosition()
{
	return Vector2(-moveVec.x, -moveVec.y);
}
