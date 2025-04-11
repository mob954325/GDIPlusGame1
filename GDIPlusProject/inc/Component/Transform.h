#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"

class Transform : public Component
{
public:
	Transform();

	void SetTransform(float posX, float posY);
	void SetTransform(Vector2 position);
	void Translate(float nextX, float nextY);
	void Translate(Vector2 position);

	Vector2 position;
	// 임시값
	float scale;
	float rotation;
};