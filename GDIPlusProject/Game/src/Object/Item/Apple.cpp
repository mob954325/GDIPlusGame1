#include "Object/Item/Apple.h"
#include "Object/Player.h"

#include "Manager/ScoreManager.h"
#include "GDIEngineLib/inc/Manager/GameTime.h"

void Apple::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetImage(L"./Resource/Item/Apple.png");
	spriteRenderer->GetImageInfo(L"apple", L"./Resource/Item/itemSize.csv");

	transform->width = 32;
	transform->height = 32;

	collider = AddComponent<Collider>();
}

void Apple::Update()
{
	animationGameTimer += g_GameTime.GetDeltaTime();

	if (animationGameTimer > maxAnimationGameTime)
	{
		spriteRenderer->currFrame++;
		spriteRenderer->currFrame %= spriteRenderer->imageFrameCount;

		animationGameTimer = 0.0f;
	}
}

void Apple::Render()
{
	spriteRenderer->DrawImage(graphics, (float)transform->position.x, (float)transform->position.y);
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

void Apple::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	// 지형 오브젝트랑 크기 맞게 변경하기
	// apple -> 32

	transform->SetTransform((float)(gridX * 64), (float)(gridY * 64));
	transform->Translate(0.0f, 36.0f);

	collider->bound = { (LONG)transform->position.x, (LONG)(transform->height * 0.7f),(LONG)(transform->width * 0.7f), (LONG)transform->position.y };
	collider->Update(this);
}
