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

	void Physics::onCollisionStarted(CollisionData data)
	{
		Collider2D* collider = data.collider;
		Physics* otherPhysics = collider->m_entity->getModule<Physics>();
		glm::vec2 otherPos = collider->m_entity->getTransform()->getPos();

		glm::vec2 thisPos = m_entity->getTransform()->getPos();
		glm::vec2 collisionDir = glm::normalize(otherPos - thisPos) * data.minDistance;

		m_entity->getTransform()->setPos(thisPos - collisionDir);
	}

	void Physics::onCollisionFinished(CollisionData data)
	{

	}

	void Physics::onCollisionStay(CollisionData data)
	{

	}
}