#include <collisions/Collidable.h>

namespace ShyEngine
{
	Collidable::Collidable() {}
	Collidable::~Collidable() {}

	void Collidable::handleCollision(bool contact)
	{
		// If it's not colliding, do nothing
		if (!contact && !m_prevContact)
			return;

		// If it started colliding, call onCollisionStarted
		if (contact && !m_prevContact)
			onCollisionStarted();
		// Otherwise, if it created contact the previous frame, call onCollisionStay
		else if (contact && m_prevContact)
			onCollisionStay();
		// If a contact ended, call onCollisionFinished
		else if (!contact && m_prevContact)
			onCollisionFinished();
	}
}