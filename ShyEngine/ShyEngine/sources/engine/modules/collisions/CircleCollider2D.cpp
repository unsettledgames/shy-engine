#include <engine/modules/collisions/CircleCollider2D.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Collider2D, CircleCollider2D);

	CircleCollider2D::CircleCollider2D() : Collider2D(nullptr) {}

	CircleCollider2D::CircleCollider2D(Entity* entity, float radius) : Collider2D(entity)
	{
		m_entity = entity;
		m_radius = radius;
	}

	bool CircleCollider2D::checkCompatibility(std::vector<Module*>& otherModules)
	{
		return true;
	}

	bool CircleCollider2D::checkDependency(std::vector<Module*>& otherModules)
	{
		return false;
	}
}