#include <engine/Entity.h>
#include <engine/System.h>
#include <util/Error.h>

namespace ShyEngine
{
	void System::addModule(Module* toAdd)
	{
		m_modulesPointers.push_back(toAdd);
	}

	int System::removeModule(Module* toRemove)
	{
		// Find the module
		auto _module = std::find(m_modulesPointers.begin(), m_modulesPointers.end(), toRemove);
		// If it exists, remove it, otherwise throw an error
		if (_module != m_modulesPointers.end())
		{
			m_modulesPointers.erase(_module);
			return 0;
		}
		else
		{
			Error::runtime("Couldn't remove the module " + toRemove->m_name + " from the system " + m_name);
			return -1;
		}
	}
}