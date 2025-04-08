#include "Component/Transform.h"

Transform::Transform()
{
	position = Vector2();
	scale = 1.0f;
	rotation = 0.0f;
}

void Transform::SetTransform(float posX, float posY)
{
	position.x = posX;
	position.y = posY;
}

void Transform::SetTransform(Vector2 position)
{
	this->position = position;
}

void Transform::Translate(float nextX, float nextY)
{
	position.x += nextX;
	position.y += nextY;
}

void Transform::Translate(Vector2 position)
{
	this->position += position;
}