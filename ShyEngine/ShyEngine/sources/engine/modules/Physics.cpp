#include <engine/modules/Physics.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Collidable, Physics)

	Physics::Physics(Entity* entity) : Collidable(entity) {}
	Physics::~Physics() {}

	void Physics::update(PhysicsData data)
	{
		if (m_static)
			return;
		Transform* transform = m_entity->getTransform();

		transform->setPos(transform->getPos() + m_velocity * data.deltaTime * data.simulationSpeed);
		m_velocity += data.gravity * data.deltaTime * m_mass * data.simulationSpeed;
	}

	// TODO: define static bodies so that they don't move
	void Physics::onCollisionStarted(CollisionData data)
	{
		contact(data);
		bump(data);
	}

	void Physics::onCollisionStay(CollisionData data)
	{
		contact(data);
		bump(data);
	}

	void Physics::onCollisionFinished(CollisionData data)
	{

	}

	void Physics::bump(CollisionData data)
	{
		Collider2D* collider = data.collider;
		Physics* otherPhysics = collider->m_entity->getModule<Physics>();

		if (otherPhysics == nullptr)
			return;
		
		float otherMass = otherPhysics->getMass();
		glm::vec2 otherVel = otherPhysics->getVelocity();
		glm::vec2 otherPos = collider->m_entity->getTransform()->getPos();

		glm::vec2 thisPos = m_entity->getTransform()->getPos();
		glm::vec2 collisionDir = glm::normalize(otherPos - thisPos) * data.minDistance;

		otherPhysics->setVelocity((((otherMass - m_mass) * otherVel +
			2 * m_mass * m_velocity) / (otherMass + m_mass)) * otherPhysics->getBounciness());
		setVelocity(((m_mass - otherMass) * m_velocity + 2 * otherMass * otherVel) / (otherMass + m_mass));
	}

	void Physics::contact(CollisionData data)
	{
		glm::vec2 thisPos = m_entity->getTransform()->getPos();
		m_entity->getTransform()->setPos(thisPos - data.minDistance);
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