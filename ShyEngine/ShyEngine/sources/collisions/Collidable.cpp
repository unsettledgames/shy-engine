#include <collisions/Collidable.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Module, Collidable);

	Collidable::Collidable() {}
	Collidable::~Collidable() {}

	void Collidable::handleCollision(bool contact, Collider2D* collidedCollider)
	{
		// If it's not colliding, do nothing
		if (!contact && !m_prevContact)
			return;

		// If it started colliding, call onCollisionStarted
		if (contact && !m_prevContact)
			onCollisionStarted(collidedCollider);
		// Otherwise, if it created contact the previous frame, call onCollisionStay
		else if (contact && m_prevContact)
			onCollisionStay(collidedCollider);
		// If a contact ended, call onCollisionFinished
		else if (!contact && m_prevContact)
			onCollisionFinished(m_currentCollider);

		m_currentCollider = collidedCollider;
	}
}