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
		auto _module = std::find(m_modulesToUpdate.begin(), m_modulesToUpdate.end(), *toRemove);
		if (_module != m_modulesToUpdate.end())
		{
			m_modulesToUpdate.erase(_module);
			return 0;
		}
		else
		{
			Error::runtime("Couldn't remove the module " + toRemove->m_name + " from the system " + m_name);
			return -1;
		}

		auto _modulePointer = std::find(m_modulesPointers.begin(), m_modulesPointers.end(), toRemove);
		if (_modulePointer != m_modulesPointers.end())
		{
			m_modulesPointers.erase(_modulePointer);
			return 0;
		}
		else
		{
			Error::runtime("Couldn't remove the module " + toRemove->m_name + " from the system " + m_name);
			return -1;
		}
	}
}