#include "Object/Item/Apple.h"
#include "Object/Player.h"

#include "Manager/ScoreManager.h"

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
}

void Apple::Render()
{
	spriteRenderer->DrawImage(graphics, (float)transform->position.x, (float)transform->position.y);
}

void Apple::OnColliderEnterImpl(GameObject* other)
{
	//Player* player = dynamic_cast<Player*>(other);

	//if (player != nullptr)
	//{
	//	g_ScoreManager.AddScore();
	//	delete this;
	//}
}

void Apple::OnColliderStayImpl(GameObject* other)
{
}

void Apple::OnColliderExitImpl(GameObject* other)
{
}

void Apple::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform((float)(gridX * spriteRenderer->imageWidth), (float)(gridY * spriteRenderer->imageHeight));

	transform->width = (float)(spriteRenderer->imageWidth * countX);
	transform->height = (float)(spriteRenderer->imageHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.y };
	collider->Update(this);
}
