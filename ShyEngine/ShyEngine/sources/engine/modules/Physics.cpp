#include <engine/modules/Physics.h>

#define CHECK_EPSILON if (m_velocity.length() < 0.1f) return;

namespace ShyEngine
{
	CLASS_DEFINITION(Collidable, Physics)

	Physics::Physics(Entity* entity) : Collidable(entity) {}
	Physics::~Physics() {}

	void Physics::update(PhysicsData data)
	{
		if (m_static)
		{
			m_velocity = glm::vec2(0, 0);
			return;
		}

		CHECK_EPSILON

		Transform* transform = m_entity->getTransform();
		glm::vec2 prevPos = transform->getPos();

		transform->setPos(transform->getPos() + m_velocity * data.deltaTime * data.simulationSpeed);
		m_velocity += data.gravity * data.deltaTime * m_mass * data.simulationSpeed;
	}

	// TODO: define static bodies so that they don't move
	void Physics::onCollisionStarted(CollisionData data)
	{
		CHECK_EPSILON
		bump(data);
	}

	void Physics::onCollisionStay(CollisionData data)
	{
		CHECK_EPSILON
		bump(data);
	}

	void Physics::onCollisionFinished(CollisionData data)
	{

	}

	void Physics::bump(CollisionData data)
	{
		Physics* otherPhysics = data.collider->m_entity->getModule<Physics>();
		// Calculate relative velocity
		glm::vec2 relativeVel = otherPhysics->getVelocity() - m_velocity;

		// Calculate relative velocity in terms of the normal direction
		float velAlongNormal = glm::dot(relativeVel, data.normal);

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0)
			return;

		// Calculate restitution
		float e = std::min(otherPhysics->getBounciness(), m_bounciness);

		// Calculate impulse scalar
		float j = -(1 + e) * velAlongNormal;
		j /= 1 / m_mass + 1 / otherPhysics->getMass();

		// Apply impulse
		glm::vec2 impulse = j * data.normal;
		setVelocity(m_velocity - 1/m_mass * impulse);
		otherPhysics->setVelocity(otherPhysics->getVelocity() + 1/otherPhysics->getMass() * impulse);
	}

	bool Physics::checkCompatibility(std::vector<Module*>& otherModules)
	{
		// There mustn't already exist a Physics component8
		return !(std::find_if(otherModules.begin(), otherModules.end(),
			[](Module* other) { return other->IsClassType(Physics::Type); }) != otherModules.end());
	}

	bool Physics::checkDependency(std::vector<Module*>& otherModules)
	{
		// TODO: can't remove a Physics module if there's at least a collider
		return false;
	}
}