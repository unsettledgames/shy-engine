#include <engine/modules/Physics.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Collidable, Physics)

	Physics::Physics(Entity* entity) : Collidable(entity) {}
	Physics::~Physics() {}

	void Physics::update(PhysicsData data)
	{
		Transform* transform = m_entity->getTransform();

		transform->setPos(transform->getPos() + m_velocity * data.deltaTime * data.simulationSpeed);
		m_velocity += data.gravity * data.deltaTime * m_mass * data.simulationSpeed;
	}

	// TODO: define static bodies so that they don't move
	void Physics::onCollisionStarted(CollisionData data)
	{
		glm::vec2 thisPos = m_entity->getTransform()->getPos();
		m_entity->getTransform()->setPos(thisPos - data.minDistance);
	}

	void Physics::onCollisionFinished(CollisionData data)
	{

	}

	void Physics::onCollisionStay(CollisionData data)
	{

	}
}