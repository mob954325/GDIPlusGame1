#include "Object/GroundObject.h"
#include "Component/Gravity.h"

GroundObject::~GroundObject()
{
}

void GroundObject::Initialize()
{
	spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->GetGraphic(&graphics);
	spriteRenderer->GetImage(L"./Resource/Tile/Blue.png");
	spriteRenderer->GetImageInfo(L"Blue", L"./Resource/Tile/tileSize.csv");

	collider = AddComponent<Collider>();
}

void GroundObject::UpdateImpl()
{
}

void GroundObject::RenderImpl()
{
}

void GroundObject::SetupTransform(int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform((float)(gridX * spriteRenderer->drawWidth), (float)(gridY * spriteRenderer->drawHeight));
	
	//printf("ground %d", spriteRenderer->drawWidth);
	
	transform->width = (float)(spriteRenderer->drawWidth * countX);
	transform->height = (float)(spriteRenderer->drawHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.y };
}

void GroundObject::OnColliderEnterImpl(GameObject* other)
{
}

void GroundObject::OnColliderExitImpl(GameObject* other)
{

}
