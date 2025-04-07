#include "Component/Transform.h"

void Transform::SetTransform(float posX, float posY)
{
	x = posX;
	y = posY;
}

void Transform::Translate(float nextX, float nextY)
{
	x += nextX;
	y += nextY;
}
