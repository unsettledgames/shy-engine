#pragma once

#include <glm/glm.hpp>
#include <data/SystemData.h>
#include <engine/System.h>

namespace ShyEngine
{
	class PhysicsManager : public System
	{
		private:
			glm::vec2 m_gravity;
		public:
			PhysicsManager();
			~PhysicsManager() {}

			void init();

			void updateModules(PhysicsData data);

			void setGravity(glm::vec2 gravity) { m_gravity = gravity; }
			glm::vec2 getGravity() { return m_gravity; }
	};
}