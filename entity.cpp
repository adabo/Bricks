#include "entity.h"

Entity::Entity(){}

Entity::Entity(float _x, float _y, float _width, float _height)
	:coord(_x,_y), dimension(_width, _height)
	//: coord.x(_x), coord.y(_y),
	 // dimension.width(_width), dimension.height(_height)
{
}

Entity::~Entity(){}

void Entity::set_sides()
{
	dimension.top = coord.y;
	dimension.bot = coord.y + dimension.height;
	dimension.left = coord.x;
	dimension.right = coord.x + dimension.width;
}



bool Entity::operator>(const Entity &_rhs) const
{
	if (dimension.left > _rhs.dimension.right) return false;
	if (dimension.right < _rhs.dimension.left) return false;
	if (dimension.bot < _rhs.dimension.top) return false;
	if (dimension.top > _rhs.dimension.bot) return false;
	return true;
}