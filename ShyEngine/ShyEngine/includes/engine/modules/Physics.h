#pragma once

#include <util/Classes.h>
#include <collisions/Collidable.h>
#include <engine/Entity.h>
#include <data/SystemData.h>

#include <glm/glm.hpp>

namespace ShyEngine
{
	class Physics : public Collidable
	{
		CLASS_DECLARATION(Physics)

		private:
			glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
			float m_mass = 1.0f;
			float m_bounciness = 1.0f;

			bool m_static = false;

			void bump(CollisionData data);

		public:
			Physics() : Collidable(nullptr) {}
			Physics(Entity* entity);
			~Physics();

			void update(PhysicsData data);

			void setVelocity(glm::vec2 vel) { m_velocity = vel; }
			glm::vec2 getVelocity() { return m_velocity; }

			void setMass(float mass) { m_mass = mass; }
			float getMass() { return m_mass; }

			void setBounciness(float b) { m_bounciness = b; }
			float getBounciness() { return m_bounciness; }

			void setStatic(bool val) { m_static = val; }
			float isStatic() { return m_static; }

			void onCollisionStarted(CollisionData data);
			void onCollisionFinished(CollisionData data);
			void onCollisionStay(CollisionData data);

			bool checkDependency(std::vector<Module*>& otherModules);
			bool checkCompatibility(std::vector<Module*>& otherModules);
	};
}