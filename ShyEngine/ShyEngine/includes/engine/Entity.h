#pragma once

#include <string>
#include <vector>
#include <util/Error.h>
#include <algorithm>
#include <util/IdGenerator.h>
#include <engine/ShyEngine.h>

namespace ShyEngine
{
	class Module;

	class Entity
	{
		friend class ShyEngine;

		protected:
			int m_id;
			IdGenerator m_ids;

			std::string m_name;
			Entity* m_reference;

			std::vector<Module> m_modules;

		public:
			friend bool operator==(const Entity& e1, const Entity& e2);
			Entity(const std::string& name);
			~Entity() { m_ids.add(m_id); }

			Module* getModule(const std::string& name);
			std::vector<Module> getModules(const std::string& name);

			void attachModule(Module& toAttach);
			int detachModule(Module& toRemove);
			void detachModules(const std::string& toRemove);

			int getId() { return m_id; }
			
			std::string getName() { return m_name; }
			void setName(const std::string& name) { m_name = name; }
	};	
}