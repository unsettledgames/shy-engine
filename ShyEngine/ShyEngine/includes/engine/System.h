#pragma once

#include <string>
#include <vector>

#include <engine/Module.h>

// REFACTOR: implement removeModule

namespace ShyEngine
{
	class Entity;

	class System
	{
		protected:
			std::vector<Module*> m_modulesPointers;
			std::vector<Module> m_modules;
			std::string m_name;

		public:
			System(const std::string& name) { m_name = name; }

			void addModule(Module* toAdd);
			int removeModule(Module* toRemove);
			void updateModules() {};
	};
}