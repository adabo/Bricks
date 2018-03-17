class Vector2D;

struct ALLEGRO_COLOR;

class Entity
{
public:
	Entity();
	~Entity();

	Vector2D coord;
	Vector2D normal;
	Vector2D side;

	ALLEGRO_COLOR color;
	float hp,
		  speed,
		  damage;

};
