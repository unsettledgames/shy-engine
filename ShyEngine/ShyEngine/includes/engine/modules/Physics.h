#pragma once

#include <util/Classes.h>
#include <engine/Module.h>
#include <engine/Entity.h>
#include <data/SystemData.h>

#include <glm/glm.hpp>

namespace ShyEngine
{
	class Physics : public Module
	{
		CLASS_DECLARATION(Physics)

		private:
			glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
			float m_mass = 1.0f;

		public:
			Physics() : Module(nullptr) {}
			Physics(Entity* entity);
			~Physics();

			void update(PhysicsData data);

			void setVelocity(glm::vec2 vel) { m_velocity = vel; }
			glm::vec2 getVelocity() { return m_velocity; }

			void setMass(float mass) { m_mass = mass; }
			float getMass() { return m_mass; }
	};
}