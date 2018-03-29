#include <math.h>
#include "vec2d.h"

Vec2D::Vec2D(float _x, float _y) : x(_x),y(_y)
{
}

Vec2D::Vec2D()
{
}

float Vec2D::get_distance(Vec2D &_sides)
{
	return sqrt(_sides.x * _sides.x + _sides.y * _sides.y);
}

void Vec2D::normalize_length(float &_cos_end, float &_sin_end)
{
	// "end" means destination or point where vector is heading
	Vec2D sides = Vec2D{_cos_end, _sin_end} - *this;
	//sides = Vec2D{_cos_end, _sin_end} - *this;
	float distance = get_distance(sides);
	x_norm = sides.x / distance;
	y_norm = sides.y / distance;
}

Vec2D Vec2D::operator+(const Vec2D &_rhs) const
{
	return Vec2D(x + _rhs.x, y + _rhs.y);
}

Vec2D Vec2D::operator*(const Vec2D &_rhs) const
{
	return Vec2D(x * _rhs.x, y * _rhs.y);
}

Vec2D Vec2D::operator-(const Vec2D &_rhs) const
{
	return Vec2D(x - _rhs.x, y - _rhs.y);
}
