#include <engine/Entity.h>

namespace ShyEngine
{
	bool Entity::operator== (Entity& other)
	{
		return other.m_id == m_id;
	}

	Module* Entity::getModule(const std::string& name)
	{
		for (auto _module : m_modulePointers)
			if (_module->getName().compare(name) == 0)
				return _module;

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
		m_modules.push_back(toAttach);
		m_modulePointers.push_back(toAttach.m_reference);
	}

	int Entity::detachModule(Module& toRemove)
	{
		// ISSUE in std::remove
		// Remove the module from the list, warn the user if it doesn't exist
		auto modIndex = std::find(m_modules.begin(), m_modules.end(), toRemove);
		if (modIndex == m_modules.end())
			Error::runtime("Couldn't find the module " + toRemove.getName() + " on the entity " + m_name + 
			" while attempting to detach it");
		m_modules.erase(modIndex);

		// Remove the module's pointer from the list of pointers
		auto pointerIndex = std::find(m_modulePointers.begin(), m_modulePointers.end(), toRemove.m_reference);
		if (pointerIndex != m_modulePointers.end())
			m_modulePointers.erase(pointerIndex);
		std::remove(m_modulePointers.begin(), m_modulePointers.end(), toRemove);
	}

	int Entity::detachModules(const std::string& name)
	{
		std::remove_if(m_modules.begin(), m_modules.end(),
			[&](Module other) {return other.getName().compare(name) == 0; });
		
		std::remove_if(m_modulePointers.begin(), m_modulePointers.end(),
			[&](Module* other) {return other->getName().compare(name) == 0; });

	}
}