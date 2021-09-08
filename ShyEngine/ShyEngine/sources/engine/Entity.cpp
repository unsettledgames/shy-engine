#include <engine/Entity.h>
#include <engine/Module.h>

namespace ShyEngine
{
	Entity::Entity(const std::string& name)
	{
		m_id = m_ids.get();
		m_name = name;
		m_modules.resize(0);
		m_transform = new Transform(this, glm::vec2(0, 0), glm::vec2(0, 0));
	}

	template <class ModuleType>
	ModuleType* Entity::getModule()
	{
		for (Module _module : this->m_modules)
			if (_module.IsClassType(ModuleType::Type))
				return static_cast<ModuleType>(_module.m_reference);

		Error::runtime("Couldn't find module " + ModuleType::m_name + " on entity " + m_name);
		return nullptr;
	}

	template <class ModuleType>
	std::vector<ModuleType*> Entity::getModules()
	{
		std::vector<ModuleType*> ret;

		for (auto _module : m_modules)
			if (_module.IsClassType(ModuleType::Type))
				ret.push_back(_module.m_reference);
		
		return ret;
	}

	template <class ModuleType, typename... Args>
	ModuleType* Entity::attachModule(Args... parameters)
	{
		ModuleType* ret = new ModuleType(parameters);

		if (ret->checkCompatibility(m_modules))
			m_modules.push_back(ret);

		return ret;
	}

	template <class ModuleType>
	void Entity::attachModule(ModuleType* toAttach)
	{
		if (toAttach->checkCompatibility(m_modules))
			m_modules.push_back(toAttach);
	}

	template <class ModuleType>
	int Entity::detachModule(ModuleType* toRemove)
	{
		int error = 0;

		// If other modules don't depend on the module I want to remove
		if (toRemove->checkDependency(m_modules))
		{
			// Remove the module from the list, warn the user if it doesn't exist
			auto modIndex = std::find(m_modules.begin(), m_modules.end(), *toRemove);

			if (modIndex == m_modules.end())
			{
				Error::runtime("Couldn't find the module " + toRemove->getName() + " on the entity " + m_name +
					" while attempting to detach it");
				error = -1;
			}
			else
				m_modules.erase(modIndex);
		}
		else
			error = -2;

		return error;
	}

	bool operator==(const Entity& e1, const Entity& e2)
	{
		return e1.m_id == e2.m_id;
	}
}