#include "Vector2.h"

Vector2::Vector2()
{
	x = 0; y = 0;
}

Vector2 Vector2::operator+(Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+=(Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-=(Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}
