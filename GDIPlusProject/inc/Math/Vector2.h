#pragma once
struct Vector2
{
public:
	Vector2();
	Vector2(float valueX, float valueY) : x(valueX), y(valueY) {}

	Vector2 operator+(Vector2& other);
	void operator+=(Vector2& other);
	Vector2 operator-(Vector2& other);
	void operator-=(Vector2& other);

	Vector2 operator*(float scalar);
	Vector2 operator*(int scalar);

public:
	float x;
	float y;
};
