#include <engine/Entity.h>
#include <engine/Module.h>

namespace ShyEngine
{
	Entity::Entity(const std::string& name)
	{
		m_id = m_ids.get();
		m_name = name;
	}

	Module* Entity::getModule(const std::string& name)
	{
		for (auto _module : m_modules)
			if (_module.getName().compare(name) == 0)
				return _module.m_reference;

		Error::runtime("Couldn't find module " + name + " on entity " + m_name);
		return nullptr;
	}

	std::vector<Module> Entity::getModules(const std::string& name)
	{
		std::vector<Module> ret;

		for (auto _module : m_modules)
			if (_module.getName().compare(name) == 0)
				ret.push_back(_module);
		
		return ret;
	}

	void Entity::attachModule(Module& toAttach)
	{
		if (toAttach.checkCompatibility(m_modules))
			m_modules.push_back(toAttach);
	}

	int Entity::detachModule(Module& toRemove)
	{
		int error = 0;

		// If other modules don't depend on the module I want to remove
		if (toRemove.checkDependency(m_modules))
		{
			// Remove the module from the list, warn the user if it doesn't exist
			auto modIndex = std::find(m_modules.begin(), m_modules.end(), toRemove);

			if (modIndex == m_modules.end())
			{
				Error::runtime("Couldn't find the module " + toRemove.getName() + " on the entity " + m_name +
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

	void Entity::detachModules(const std::string& name)
	{
		std::remove_if(m_modules.begin(), m_modules.end(),
			[&](Module other) {return other.getName().compare(name) == 0 && other.checkDependency(m_modules); });
	}

	bool operator==(const Entity& e1, const Entity& e2)
	{
		return e1.m_id == e2.m_id;
	}
}