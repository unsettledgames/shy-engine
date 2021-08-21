#pragma once

#include <engine/Module.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class Transform : public Module
	{
		private:
			glm::vec2 m_position;
			glm::vec2 m_scale;

			float m_angleRotation;

		public:
			Transform();
			Transform(Entity* entity, glm::vec2 pos);
			Transform(Entity* entity, glm::vec2 pos, glm::vec2 scale);
			Transform(Entity* entity, glm::vec2 pos, glm::vec2 scale, float angle);

			bool checkDependency(std::vector<Module>& otherModules);
			bool checkCompatibility(std::vector<Module>& otherModules);

			glm::vec2 getPos() { return m_position; }
			glm::vec2 getScale() { return m_scale; }
			float getAngle() { return m_angleRotation; }

			void setPos(glm::vec2 pos) { m_position = pos; }
			void setScale(glm::vec2 scale) { m_scale = scale; }
			void setAngle(float angle) { m_angleRotation = angle; }

	};
}