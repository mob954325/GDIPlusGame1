#include "Object/Flag.h"
#include "Object/Player.h"
#include "Manager/GameManager.h"

Flag::~Flag()
{
}

void Flag::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	spriteRenderer->GetImage(L"./Resource/Item/End.png", false);
	spriteRenderer->GetImageInfo(L"end", L"./Resource/Item/itemSize.csv");

	transform->width = 64;
	transform->height = 64;

	collider = AddComponent<Collider>();
}

void Flag::UpdateImpl()
{
}

void Flag::RenderImpl()
{
#if _DEBUG
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0), 2.0f); // »¡°£»ö, µÎ²² 1
	graphics->DrawRectangle(
		&pen,
		(INT)(collider->bound.left),
		(INT)(collider->bound.bottom),
		(INT)(collider->bound.right - collider->bound.left),
		(INT)(collider->bound.top - collider->bound.bottom)
	);
#endif
}

void Flag::OnColliderEnterImpl(GameObject* other)
{
	Player* player = static_cast<Player*>(other);
	if (player != nullptr)
	{
		g_GameManager.gameState = GameState::End;
	}
}

void Flag::OnColliderStayImpl(GameObject* other)
{
}

void Flag::OnColliderExitImpl(GameObject* other)
{
}

void Flag::SetupData(int gridSize, int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform((float)(gridX * gridSize), (float)(gridY * gridSize));

	transform->width = (float)(gridSize * countX);
	transform->height = (float)(gridSize * countY);
	collider->bound =
	{
		(LONG)(gridX * gridSize),
		(LONG)((gridY + countY) * gridSize),
		(LONG)((gridX + countX) * gridSize),
		(LONG)(gridY * gridSize)
	};
}