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

	bool CircleCollider2D::checkCollision(Collider2D* coll)
	{
		CircleCollider2D* other = (CircleCollider2D*)coll;
		glm::vec2 otherPos = other->m_transform->getPos();
		glm::vec2 pos = m_transform->getPos();

		return std::sqrtf((otherPos.x + pos.x) * (otherPos.x + pos.x) +
			(otherPos.y + pos.y) * (otherPos.y + pos.y)) >
			(other->m_radius + m_radius);
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