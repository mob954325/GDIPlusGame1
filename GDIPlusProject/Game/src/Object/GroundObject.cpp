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
	
	transform->width = (float)(gridSize * countX);
	transform->height = (float)(gridSize * countY);
	collider->bound =
	{
		(LONG)(gridX * gridSize),
		(LONG)((gridY + countY) * gridSize),
		(LONG)((gridX + countX) * gridSize),
		(LONG)(gridY * gridSize)
	};

	//printf("ground : width, height, bound\n");
	printf("%f %f | %d %d %d %d\n", transform->width, transform->height, collider->bound.left, collider->bound.top, collider->bound.right, collider->bound.bottom);
}

void GroundObject::OnColliderEnterImpl(GameObject* other)
{
}

void GroundObject::OnColliderExitImpl(GameObject* other)
{

}
