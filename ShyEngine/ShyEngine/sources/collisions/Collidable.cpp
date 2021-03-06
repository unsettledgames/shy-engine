#include <collisions/Collidable.h>
#include <engine/modules/collisions/RectCollider2D.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Module, Collidable);

	Collidable::Collidable() {}
	Collidable::~Collidable() {}

	// IMPROVEMENT: handle more than 1 collider at once
	void Collidable::handleCollision(CollisionData data)
	{
		// If it's not colliding, do nothing
		if (!data.colliding && !m_prevContact)
			return;

		// If it started colliding, call onCollisionStarted
		if (data.colliding && !m_prevContact)
			onCollisionStarted(data);
		// Otherwise, if it created contact the previous frame, call onCollisionStay because it's keeping contact
		else if (data.colliding && m_prevContact)
			onCollisionStay(data);
		// If a contact ended, call onCollisionFinished
		else if (!data.colliding && m_prevContact)
			onCollisionFinished(data);

		// Save the last contact state and the collider the object is colliding with
		m_prevContact = data.colliding;
		m_currentCollider = data.collider;
	}
}