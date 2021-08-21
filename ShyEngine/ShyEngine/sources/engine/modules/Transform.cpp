#include <engine/modules/Transform.h>

namespace ShyEngine
{
	Transform::Transform() : Module("Transform", nullptr)
	{
		m_position = glm::vec2(0, 0);
		m_scale = glm::vec2(1, 1);
		m_angleRotation = 0;
	}

	Transform::Transform(Entity* entity, glm::vec2 pos) : Module("Transform", entity)
	{
		m_position = pos;
		m_scale = glm::vec2(1, 1);
		m_angleRotation = 0;
	}

	Transform::Transform(Entity* entity, glm::vec2 pos, glm::vec2 scale) : Module("Transform", entity)
	{
		m_position = pos;
		m_scale = scale;
		m_angleRotation = 0;
	}

	Transform::Transform(Entity* entity, glm::vec2 pos, glm::vec2 scale, float angle) : Module("Transform", entity)
	{
		m_position = pos;
		m_scale = scale;
		m_angleRotation = angle;
	}

	bool Transform::checkDependency(std::vector<Module>& otherModules)
	{
		// Sprite depends on Transform, so there shouldn't be a Sprite
		return std::find_if(otherModules.begin(), otherModules.end(),
			[](Module& other) { return other.getName() == "Sprite"; }) == otherModules.end();
	}

	bool Transform::checkCompatibility(std::vector<Module>& otherModules)
	{
		// There shouldn't be another Transform module when adding one
		return std::find_if(otherModules.begin(), otherModules.end(),
			[](Module& other) { return other.getName() == "Transform"; }) == otherModules.end();
	}
}