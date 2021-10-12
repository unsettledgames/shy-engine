#include <engine/systems/UserScriptsManager.h>
#include <engine/modules/UserScript.h>

namespace ShyEngine
{
	void UserScriptsManager::init()
	{
		// Call the init functions for each script
		for (int i = 0; i < m_modulesPointers.size(); i++)
			((UserScript*)m_modulesPointers[i])->init();
	}

	void UserScriptsManager::updateModules()
	{
		// Call the update functions for each script
		for (int i = 0; i < m_modulesPointers.size(); i++)
			((UserScript*)m_modulesPointers[i])->update();
	}
}