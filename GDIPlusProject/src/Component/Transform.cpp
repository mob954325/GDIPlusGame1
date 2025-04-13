#include "Component/Transform.h"

Transform::Transform()
{
	position = Vector2();
	width = 1.0f;
	height = 1.0f;
	scale = 1.0f;
	rotation = 0.0f;
}

Transform::Transform(Vector2 position, float width, float height)
{
	position = Vector2(position);
	this->width = width;
	this->height = height;
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

#include <iostream>
void Transform::Translate(Vector2 position) // 임시
{
	this->position += position;
}