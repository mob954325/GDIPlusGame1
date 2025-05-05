#include "Object/Item/Apple.h"
#include "Object/Player.h"

#include "Manager/ScoreManager.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"

void Apple::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);

	spriteRenderer->GetImage(L"./Resource/Item/Apple.png");
	spriteRenderer->GetImageInfo(L"apple", L"./Resource/Item/itemSize.csv");

	transform->width = 32;
	transform->height = 32;

	collider = AddComponent<Collider>();
	collider->bound = { (LONG)transform->position.x, (LONG)(transform->height * 0.7f),(LONG)(transform->width * 0.7f), (LONG)transform->position.y };

}

void Apple::UpdateImpl()
{
	//animationGameTimer += g_GameTime.GetDeltaTime();

	//if (animationGameTimer > maxAnimationGameTime)
	//{
	//	spriteRenderer->currFrame++;
	//	spriteRenderer->currFrame %= spriteRenderer->imageFrameCount;

	//	animationGameTimer = 0.0f;
	//}
}

void Apple::RenderImpl()
{
}

void Apple::OnColliderEnterImpl(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);

	if (player != nullptr)
	{
		g_ScoreManager.AddScore();
		shouldBeDeleted = true;
	}
}

void Apple::OnColliderStayImpl(GameObject* other)
{
}

void Apple::OnColliderExitImpl(GameObject* other)
{
}

void Apple::SetupTransform(int gridSize, int gridX, int gridY, int countX, int countY)
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