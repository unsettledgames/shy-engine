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

	CollisionData CircleCollider2D::checkCollision(Collider2D* coll)
	{
		CollisionData ret;
		CircleCollider2D* other = (CircleCollider2D*)coll;

		glm::vec2 otherPos = other->m_transform->getPos();
		glm::vec2 pos = m_transform->getPos();

		float distance = std::sqrtf((otherPos.x - pos.x) * (otherPos.x - pos.x) +
			(otherPos.y - pos.y) * (otherPos.y - pos.y));
		float radiusSum = other->m_radius + m_radius;

		ret.collider = coll;
		ret.minDistance = radiusSum - distance;
		ret.colliding = distance <= radiusSum;

		return ret;
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