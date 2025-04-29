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
	transform->SetTransform((float)(gridX * spriteRenderer->imageWidth), (float)(gridY * spriteRenderer->imageHeight));
	
	//printf("ground %d", spriteRenderer->imageWidth);
	
	transform->width = (float)(spriteRenderer->imageWidth * countX);
	transform->height = (float)(spriteRenderer->imageHeight * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.y };
}

void GroundObject::OnColliderEnterImpl(GameObject* other)
{
}

void GroundObject::OnColliderExitImpl(GameObject* other)
{

}
