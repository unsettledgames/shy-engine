#pragma once

#include <engine/Module.h>
#include <engine/Entity.h>
#include <data/SystemData.h>

#include <glm/glm.hpp>

namespace ShyEngine
{
	class Physics : public Module
	{
		private:
			glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);

		public:
			Physics() : Module("Physics", nullptr) {}
			Physics(Entity* entity);
			~Physics();

			void update(PhysicsData data);

			void setVelocity(glm::vec2 vel) { m_velocity = vel; }
			glm::vec2 getVelocity() { return m_velocity; }
	};
}