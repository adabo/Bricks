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

void Vector2D::normalize_length(_x_end, &_y_end)
{
	*this = *this - Vector2D{_x_end, _y_end};
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
