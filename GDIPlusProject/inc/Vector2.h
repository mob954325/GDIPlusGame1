#pragma once
struct Vector2
{
public:
	Vector2();
	Vector2(float valueX, float valueY) : x(valueX), y(valueY) {}
	Vector2 operator+(Vector2& other);
	Vector2 operator+=(Vector2& other);
	Vector2 operator-(Vector2& other);
	Vector2 operator-=(Vector2& other);

public:
	float x;
	float y;

};
