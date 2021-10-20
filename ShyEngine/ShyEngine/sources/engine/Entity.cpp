#include <engine/Entity.h>
#include <engine/Module.h>

namespace ShyEngine
{
	Entity::Entity(const std::string& name)
	{
		m_name = name;

		// The entity must have at least a transform component
		m_transform = new Transform(this, glm::vec2(0, 0), glm::vec2(1, 1));
		m_modules.push_back(m_transform);
	}

	bool operator==(const Entity& e1, const Entity& e2)
	{
		// Two entities are the same if they have the same id
		return e1.m_id == e2.m_id;
	}
}