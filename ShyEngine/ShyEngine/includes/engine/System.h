#pragma once

#include <engine/Module.h>
#include <engine/Entity.h>
#include <string>

namespace ShyEngine
{
	class System
	{
		protected:
			std::vector<Module> m_modulesToUpdate;
			std::string m_name;

		public:
			System(const std::string& name) { m_name = name; }

			void addModule(Module toAdd);
			int removeModule(Module toRemove);
			void updateModules() {};
	};
}