#include <engine/Entity.h>
#include <engine/Module.h>

namespace ShyEngine
{
	Entity::Entity(const std::string& name)
	{
		m_id = m_ids.get();
		m_name = name;

		m_transform = new Transform(this, glm::vec2(0, 0), glm::vec2(0, 0));
		m_modules.push_back(m_transform);
	}

	bool operator==(const Entity& e1, const Entity& e2)
	{
		return e1.m_id == e2.m_id;
	}
}