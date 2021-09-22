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

	void Physics::onCollisionStarted(Collider2D* collider)
	{
		Physics* otherPhysics = collider->m_entity->getModule<Physics>();
		float otherMass = otherPhysics->getMass();
		glm::vec2 otherVel = otherPhysics->getVelocity();

		otherPhysics->setVelocity(((otherMass - m_mass) * otherVel + 2 * m_mass * m_velocity) / (otherMass + m_mass));
		setVelocity(((m_mass - otherMass) * m_velocity + 2 * otherMass * otherVel) / (otherMass + m_mass));
	}

	void Physics::onCollisionFinished(Collider2D* collider)
	{

	}

	void Physics::onCollisionStay(Collider2D* collider)
	{

	}
}