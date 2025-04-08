#pragma once

class Transform
{
public:
	void SetTransform(float posX, float posY);
	void Translate(float nextX, float nextY);

	// 임시 값
	float x;
	float y;
	float scale;
	float rotation;
};