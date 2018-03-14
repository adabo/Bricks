#include "vector2D.h"

Vector2D::Vector2D(Coordinate _coord)
{
}

Vector2D::Vector2D(Vector2D _vec1, Vector2D _vec2)
{
}

Vector2D::~Vector2D()
{
}

void Vector2D::get_normalized_vector(Vector2D &_destination)
{
	Vector2D temp = _destination - *this; // start.x - end.x, start.y - end.y
	float distance = sqrt(temp.x * temp.x + temp.y * temp.y); // a*a+b*b=c*c
	temp = temp / distance; // Normalize side a and b;
	x = temp.x;
	y = temp.y;
}

Coordinate Vector2D::operator/(const float &_distance) const
{
	return Coordinate(x / _distance, y / _distance);
}

Coordinate Vector2D::operator+(const Vector2D &_rhs) const
{
	return Coordinate(x + _rhs.x, y + _rhs.y);
}

Coordinate Vector2D::operator*(const Vector2D &_rhs) const
{
	return Coordinate(x * _rhs.x, y * _rhs.y);
}

Coordinate Vector2D::operator-(const Vector2D &_rhs) const
{
	return Coordinate(x - _rhs.x, y - _rhs.y);
}
