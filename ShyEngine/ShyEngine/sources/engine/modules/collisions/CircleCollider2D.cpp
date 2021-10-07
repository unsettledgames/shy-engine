#include <engine/modules/collisions/CircleCollider2D.h>
#include <engine/modules/collisions/RectCollider2D.h>

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

		if (coll->IsClassType(CircleCollider2D::Type))
		{
			CircleCollider2D* other = (CircleCollider2D*)coll;

			glm::vec2 otherPos = other->m_transform->getPos();
			glm::vec2 pos = m_transform->getPos();

			float distance = std::sqrtf((otherPos.x - pos.x) * (otherPos.x - pos.x) +
				(otherPos.y - pos.y) * (otherPos.y - pos.y));
			float radiusSum = other->m_radius + m_radius;

			ret.colliding = distance <= radiusSum;
			if (ret.colliding)
			{
				ret.normal = glm::normalize(otherPos - pos);
				ret.minDistance = glm::normalize(otherPos - pos) * (radiusSum - distance);
			}
			
		}
		else if (coll->IsClassType(RectCollider2D::Type))
		{
			RectCollider2D* other = (RectCollider2D*)coll;

			ret.colliding = AABB(other->getRectBounds(), glm::vec4(m_transform->getPos(), glm::vec2(m_radius, m_radius) * 2.0f), &ret.minDistance);
			
			if (ret.colliding)
			{
				glm::vec2 thisPos = m_transform->getPos();
				glm::vec4 otherBox = other->getRectBounds();

				glm::vec2 nearestPoint = glm::vec2(
					std::max(thisPos.x, otherBox.x + otherBox.z),
					std::max(thisPos.y, otherBox.y + otherBox.w)
				);
				glm::vec2 distance = thisPos - nearestPoint;
				
				// Compute the normal
				ret.normal = glm::normalize(glm::vec2(-distance.y, distance.x));
				// Compute penetration depth
				ret.minDistance = (abs(ret.minDistance.x) > abs(ret.minDistance.y) ? 
					glm::vec2(0, -ret.minDistance.y) : glm::vec2(-ret.minDistance.x, 0));
			}
		}
		
		ret.collider = coll;

		return ret;
	}
}