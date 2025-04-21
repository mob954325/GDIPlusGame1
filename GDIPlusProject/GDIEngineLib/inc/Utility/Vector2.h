#pragma once
#include <float.h>
#include <math.h>

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float valueX, float valueY);
	Vector2(int valueX, int valueY);

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);

	Vector2 operator*(float other);
	Vector2 operator*(int other);
	Vector2 operator/(float other);
	Vector2 operator/(int other);

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	bool IsZero();
	float Dot(const Vector2& other);
	float Length();
	float LengthSQ();
	Vector2 Normalize();
};