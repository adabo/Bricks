#include "entity.h"

Entity::Entity(){}

Entity::Entity(Vector2D _coord, Dimension _dimension, float _speed)
	:coord(_coord), dimension(_dimension), speed(_speed)
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
