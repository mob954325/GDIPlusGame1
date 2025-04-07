#pragma once

class Transform
{
public:
	void SetTransform(float posX, float posY);
	void Translate(float nextX, float nextY);

	// ÀÓ½Ã °ª
	float x;
	float y;
	float scale;
	float rotation;
};