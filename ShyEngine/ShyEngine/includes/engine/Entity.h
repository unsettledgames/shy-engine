#pragma once

#include <string>
#include <vector>
#include <util/Error.h>
#include <algorithm>
#include <engine/Module.h>

namespace ShyEngine
{
	class Entity
	{
		private:
			int m_id;
			std::string m_name;
			Entity* m_reference;

			std::vector<Module> m_modules;
			std::vector<Module*> m_modulePointers;

		public:
			bool operator== (Entity& other);

			Module* getModule(const std::string& name);
			std::vector<Module> getModules(const std::string& name);

			void attachModule(Module& toAttach);
			int detachModule(Module& toRemove);
			int detachModules(const std::string& toRemove);

			int getId() { return m_id; }
			
			std::string getName() { return m_name; }
			void setName(const std::string& name) { m_name = name; }
	};
}