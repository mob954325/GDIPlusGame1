#include "pch.h"
#include "Utility/Component.h"

Component::Component()
{
	owner = nullptr;
}

Component::~Component()
{
}

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::Render()
{
}

void Component::SetActive(bool value)
{
	isActive = value;
}

bool Component::GetIsActive()
{
	return isActive;
}
