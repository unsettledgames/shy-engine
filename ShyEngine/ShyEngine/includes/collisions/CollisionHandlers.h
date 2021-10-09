#pragma once

#include <data/SystemData.h>

#include <engine/modules/collisions/CircleCollider2D.h>
#include <engine/modules/collisions/RectCollider2D.h>

namespace ShyEngine
{
	CollisionData circleVsRect(CircleCollider2D* circle, RectCollider2D* rect);
	CollisionData rectVsRect(RectCollider2D* first, RectCollider2D* second);
	CollisionData circleVsCircle(CircleCollider2D* first, CircleCollider2D* second);

	CollisionData checkCollision(Collider2D* first, Collider2D* second);
}