#pragma once

#include <math.h>
#include "coordinate.h"

class Vector2D
{
public:
	Vector2D(Coordinate _coord);
	Vector2D(Vector2D _vec1, Vector2D _vec2);
	virtual ~Vector2D();
	void get_normalized_vector(Vector2D &_destination);

	Coordinate operator/(const float &_distance) const;
	Coordinate operator*(const Vector2D &_rhs) const;
	Coordinate operator+(const Vector2D &_rhs) const;
	Coordinate operator-(const Vector2D &_rhs) const;

	float x, y;
	Coordinate coord;
};

