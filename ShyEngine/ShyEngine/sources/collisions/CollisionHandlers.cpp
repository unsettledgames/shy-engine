#include <collisions/CollisionHandlers.h>

namespace ShyEngine
{
	CollisionData circleVsCircle(CircleCollider2D* first, CircleCollider2D* second)
	{
		/*
			Circle vs circle collisions are quite simple:
			- If the distance between the 2 objects is less than the sum of their radii, the objects are colliding
			- The normal is just the distance between the 2 objects, normalized
		*/
		CollisionData ret;

		glm::vec2 otherPos = second->getTransform()->getPos();
		glm::vec2 pos = first->getTransform()->getPos();

		float distance = std::sqrtf((otherPos.x - pos.x) * (otherPos.x - pos.x) +
			(otherPos.y - pos.y) * (otherPos.y - pos.y));
		float radiusSum = second->getRadius() + first->getRadius();

		ret.colliding = distance <= radiusSum;
		if (ret.colliding)
			ret.normal = glm::normalize(otherPos - pos);

		return ret;
	}

	CollisionData circleVsRect(CircleCollider2D* circle, RectCollider2D* rect)
	{
		CollisionData ret;

		/*
			Circle vs rect collisions are more elaborate:
			- Whether the objects are colliding or not is determined by a simple AABB
				IMPROVEMENT: Is this precise enough?
			- The normal is harder to compute: we have to get the nearest point of collision on the rect,
				get the distance from the circle to that point and finally normalize the vector (-distance.y, distance.x)
					

		*/

		ret.colliding = Collider2D::AABB(
			rect->getRectBounds(), glm::vec4(circle->getTransform()->getPos(), 
			glm::vec2(circle->getRadius(), circle->getRadius()) * 2.0f)
		);

		if (ret.colliding)
		{
			glm::vec2 thisPos = circle->getTransform()->getPos();
			glm::vec4 otherBox = rect->getRectBounds();

			glm::vec2 nearestPoint = glm::vec2(
				std::max(thisPos.x, otherBox.x + otherBox.z),
				std::max(thisPos.y, otherBox.y + otherBox.w)
			);
			glm::vec2 distance = thisPos - nearestPoint;

			// Compute the normal
			ret.normal = glm::normalize(glm::vec2(-distance.y, distance.x));
		}

		return ret;
	}

	CollisionData rectVsRect(RectCollider2D* first, RectCollider2D* second)
	{
		// TODO
		CollisionData ret;

		return ret;
	}

	CollisionData checkCollision(Collider2D* first, Collider2D* second)
	{
		CollisionData ret;

		if (first->IsClassType(RectCollider2D::Type))
		{
			// Rect - Circle
			if (second->IsClassType(CircleCollider2D::Type))
				ret = circleVsRect((CircleCollider2D*)second, (RectCollider2D*)first);
			// Rect - Rect
			else if (second->IsClassType(RectCollider2D::Type))
				ret = rectVsRect((RectCollider2D*)second, (RectCollider2D*)first);

			ret.collider = first;
		}
		else if (first->IsClassType(CircleCollider2D::Type))
		{
			// Circle - Cirlce
			if (second->IsClassType(CircleCollider2D::Type))
				ret = circleVsCircle((CircleCollider2D*)first, (CircleCollider2D*)second);
			// Circle - Rect
			else if (second->IsClassType(RectCollider2D::Type))
				ret = circleVsRect((CircleCollider2D*)first, (RectCollider2D*)second);

			ret.collider = second;
		}

		return ret;
	}
}