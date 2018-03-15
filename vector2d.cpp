#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
}

Vector2D::~Vector2D(){}

Vector2D::Vector2D(float _x, float _y)
	:	x(_x),
		y(_y)
{
}

float Vector2D::get_distance()
{
	return sqrt(x * x + y * y);
}

void Vector2D::normalize_length(float _x_end, float &_y_end)
{
	Vector2D sides;
	sides = Vector2D{_x_end, _y_end} - *this;
	float distance = get_distance();
	x_normal = x / distance;
	y_normal = y / distance;
}

Vector2D Vector2D::operator+(const Vector2D &vector_input) const
{
	return Vector2D(x + vector_input.x, y + vector_input.y);
}

Vector2D Vector2D::operator*(const Vector2D &vector_input) const
{
	return Vector2D(x * vector_input.x, y * vector_input.y);
}

Vector2D Vector2D::operator-(const Vector2D &vector_input) const
{
	return Vector2D(x - vector_input.x, y - vector_input.y);
}
