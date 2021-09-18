#include <engine/modules/Physics.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Collidable, Physics)

	Physics::Physics(Entity* entity) : Collidable(entity) {}
	Physics::~Physics() {}

	void Physics::update(PhysicsData data)
	{
		Transform* transform = m_entity->getTransform();

		transform->setPos(transform->getPos() + m_velocity * data.deltaTime );
		m_velocity += data.gravity * data.deltaTime * m_mass;
	}
}