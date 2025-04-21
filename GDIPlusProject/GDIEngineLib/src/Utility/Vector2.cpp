#include "pch.h"
#include "Utility/Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float valueX, float valueY)
{
	x = valueX;
	y = valueY;
}

Vector2::Vector2(int valueX, int valueY)
{
	x = (float)valueX;
	y = (float)valueY;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float other)
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator*(int other)
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(float other)
{
	return Vector2(x / other, y / other);
}

Vector2 Vector2::operator/(int other)
{
	return Vector2(x / other, y / other);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x; y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x; y -= other.y;
	return *this;
}

bool Vector2::IsZero()
{
	return x < FLT_EPSILON + 1.1e-13f && y < FLT_EPSILON + 1.1e-13f;
}

float Vector2::Dot(const Vector2& other)
{
	return x * other.x + y * other.y;
}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

float Vector2::LengthSQ()
{
	return x * x + y * y;
}

Vector2 Vector2::Normalize()
{
	float len = len = Length();
	if (len < FLT_EPSILON) // or Len == 0
		return Vector2(0.0f, 0.0f);

	return Vector2(x / Length(), y / Length());
}