#include <engine/modules/collisions/CircleCollider2D.h>

namespace ShyEngine
{
	CircleCollider2D::CircleCollider2D() {}

	CircleCollider2D::CircleCollider2D(Entity* entity, float radius) : Collider2D(entity)
	{
		m_radius = radius;
	}

}