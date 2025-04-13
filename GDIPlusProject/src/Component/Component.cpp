#include "./Component/Component.h"

Component::~Component()
{
	//delete owner;
}

void Component::SetOwner(GameObject* object)
{
	owner = object;
}