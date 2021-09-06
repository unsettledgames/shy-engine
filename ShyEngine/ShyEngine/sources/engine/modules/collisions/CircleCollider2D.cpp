#include <engine/modules/collisions/CircleCollider2D.h>

namespace ShyEngine
{
	CircleCollider2D::CircleCollider2D() {}

	CircleCollider2D::CircleCollider2D(float radius) 
	{
		m_radius = radius;
	}

}