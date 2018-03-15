#include <iostream>

class Vector2D
{
public:
	Vector2D();
	~Vector2D();
	Vector2D(float _x, float _y);
	Vector2D(Vector2D &_v0, Vector2D &_v1);

	float get_distance();
	void get_normal(float _distance);

	Vector2D operator*(const Vector2D &vector_input) const;
	Vector2D operator+(const Vector2D &vector_input) const;
	Vector2D operator-(const Vector2D &vector_input) const;

	float x, y;
	float normal_x, normal_y;
};
