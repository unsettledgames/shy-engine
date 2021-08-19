#include <engine/System.h>
#include <util/Error.h>

namespace ShyEngine
{
	void System::addModule(Module toAdd)
	{
		m_modulesToUpdate.push_back(toAdd);
	}

	int System::removeModule(Module toRemove)
	{
		auto _module = std::find(m_modulesToUpdate.begin(), m_modulesToUpdate.end(), toRemove);
		if (_module != m_modulesToUpdate.end())
		{
			m_modulesToUpdate.erase(_module);
			return 0;
		}
		else
		{
			Error::runtime("Couldn't remove the module " + toRemove.m_name + " from the system " + m_name);
			return -1;
		}
	}
}