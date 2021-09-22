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

	void Physics::onCollisionStarted(Collider2D* collider)
	{
		Physics* otherPhysics = collider->m_entity->getModule<Physics>();
		float otherMass = otherPhysics->getMass();
		glm::vec2 otherVel = otherPhysics->getVelocity();
		glm::vec2 otherPos = collider->m_entity->getTransform()->getPos();

		glm::vec2 thisPos = m_entity->getTransform()->getPos();

		// Make sure the object doesn't interpenetrate with the other
		/*
			- Difference between otherPos and thisPos to get the direction
			- Normalize the direction, multiply it by the amount the objects are colliding
			- Add the resulting vector to the position

			ISSUE: I need to pass the minimum distance the objects should keep. Need to pass CollisionData so that
				I an expand it or refactor it in the future
		*/
		glm::vec2 collisionDir = glm::normalize(otherPos - thisPos);

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