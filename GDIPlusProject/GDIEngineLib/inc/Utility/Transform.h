#pragma once
#include "Vector2.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Transform(GameObject* obj) : Component(obj) { };

	void SetTransform(float posX, float posY);
	void SetTransform(Vector2 position);
	void Translate(float nextX, float nextY);
	void Translate(Vector2 position);

	Vector2 position;
	float width = 0;
	float height = 0;
};