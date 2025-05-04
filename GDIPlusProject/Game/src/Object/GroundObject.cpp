#include "Object/GroundObject.h"
#include "Component/Gravity.h"

GroundObject::~GroundObject()
{
}

void GroundObject::Initialize()
{
	collider = AddComponent<Collider>();
}

void GroundObject::UpdateImpl()
{
}

void GroundObject::RenderImpl()
{
}

void GroundObject::SetupTransform(int gridSize, int gridX, int gridY, int countX, int countY)
{
	transform->SetTransform((float)(gridX * gridSize), (float)(gridY * gridSize));
	
	//printf("ground %d", spriteRenderer->drawWidth);
	
	transform->width = (float)(gridSize * countX);
	transform->height = (float)(gridSize * countY);
	collider->bound = { (LONG)transform->position.x, (LONG)transform->height,(LONG)transform->width, (LONG)transform->position.y };
}

void GroundObject::OnColliderEnterImpl(GameObject* other)
{
}

void GroundObject::OnColliderExitImpl(GameObject* other)
{

}
