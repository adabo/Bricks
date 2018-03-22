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

float Vector2D::get_distance(Vector2D &_sides)
{
	return sqrt(_sides.x * _sides.x + _sides.y * _sides.y);
}

void Vector2D::normalize_length(float &_x_end, float &_y_end)
{
	// "end" means destination or point where vector is heading
	Vector2D sides;
	sides = Vector2D{_x_end, _y_end} - *this;
	float distance = get_distance(sides);
	x_normal = sides.x / distance;
	y_normal = sides.y / distance;
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
