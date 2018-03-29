#pragma once

class Vec2D
{
public:
	Vec2D(float _x,float _y);
	Vec2D();
	float x,y,
		  x_norm, y_norm;

	Vec2D operator*(const Vec2D &_rhs) const;
	Vec2D operator+(const Vec2D &_rhs) const;
	Vec2D operator-(const Vec2D &_rhs) const;

	float get_distance(Vec2D &_sides);
	void normalize_length(float &_cos_end,float &_sin_end);
};
