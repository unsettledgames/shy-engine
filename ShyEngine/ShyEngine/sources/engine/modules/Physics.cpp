#include <engine/modules/Physics.h>

namespace ShyEngine
{
	Physics::Physics(Entity* entity) : Module("Physics", entity) {}
	Physics::~Physics() {}

	void Physics::update(PhysicsData data)
	{
		Transform* transform = m_entity->getTransform();

		transform->setPos(transform->getPos() + m_velocity * data.deltaTime);
		m_velocity += data.gravity * data.deltaTime;
	}
}