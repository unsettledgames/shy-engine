#include <collisions/Collidable.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Module, Collidable);

	Collidable::Collidable() {}
	Collidable::~Collidable() {}

	void Collidable::handleCollision(CollisionData data)
	{
		// If it's not colliding, do nothing
		if (!data.colliding && !m_prevContact)
			return;

		// If it started colliding, call onCollisionStarted
		if (data.colliding && !m_prevContact)
			onCollisionStarted(data);
		// Otherwise, if it created contact the previous frame, call onCollisionStay
		else if (data.colliding && m_prevContact)
			onCollisionStay(data);
		// If a contact ended, call onCollisionFinished
		else if (!data.colliding && m_prevContact)
			onCollisionFinished(data);

		m_currentCollider = data.collider;
	}
}