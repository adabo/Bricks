#include <iostream>

class Vector2D
{
public:
	Vector2D();
	~Vector2D();
	Vector2D(float _x, float _y);
	Vector2D(Vector2D &_v0, Vector2D &_v1);

	void normalize_length(float _x_end, float &_y_end);
	float get_distance();

	Vector2D operator*(const Vector2D &vector_input) const;
	Vector2D operator+(const Vector2D &vector_input) const;
	Vector2D operator-(const Vector2D &vector_input) const;

	float x, y;
	float x_normal, y_normal;
};
