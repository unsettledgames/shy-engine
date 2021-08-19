#pragma once

#include <engine/Module.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	class System
	{
		private:
			std::vector<Module> m_modulesToUpdate;

		public:
			void addModule(Module toAdd);
			void removeModule(Module toRemove);
	};
}