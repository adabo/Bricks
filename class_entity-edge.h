#pragma once

#include "class_entity.h"

class Edge: public Entity
{
public:
	void update_coords();
	void update_dimensions();
	void update_colliding();
	void draw();
};
