#pragma once

#include <ShyEngine/includes/engine/ShyEngine.h>

class ElasticBump : ShyEngine::UserScript
{
	private:
		ShyEngine::Physics* m_physics;
	public:
		void init() override { m_physics = m_entity->getModule<ShyEngine::Physics>(); }
		void update() override {}

		void onCollisionStarted(ShyEngine::CollisionData data)
		{
			ShyEngine::Collider2D* collider = data.collider;
			ShyEngine::Physics* otherPhysics = collider->m_entity->getModule<ShyEngine::Physics>();
			float otherMass = otherPhysics->getMass();
			glm::vec2 otherVel = otherPhysics->getVelocity();
			glm::vec2 otherPos = collider->m_entity->getTransform()->getPos();

			glm::vec2 thisPos = m_entity->getTransform()->getPos();
			glm::vec2 collisionDir = glm::normalize(otherPos - thisPos) * data.minDistance;

			otherPhysics->setVelocity(((otherMass - m_physics->getMass()) * otherVel + 
				2 * m_physics->getMass() * m_physics->getVelocity()) / (otherMass + m_physics->getMass()));
			m_physics->setVelocity(((m_physics->getMass() - otherMass) * m_physics->getVelocity() + 2 * otherMass * otherVel) / (otherMass + m_physics->getMass()));
		}
};