#pragma once

#include <string>
#include <vector>
#include <util/Error.h>
#include <algorithm>

#include <collisions/Collidable.h>
#include <engine/modules/Transform.h>
#include <util/IdGenerator.h>

// BUG: Id system is wrong, should be a member of the engine instead
// REFACTOR: if registering a module to the entity's only purpose is to set the entity, why shouldn't this happen
//		in the module constructor?

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
			Transform* m_transform;

		public:
			friend bool operator==(const Entity& e1, const Entity& e2);
			Entity(const std::string& name);
			~Entity() { m_ids.add(m_id); }

			template <class ModuleType>
			ModuleType* getModule();

			template <class ModuleType>
			std::vector<ModuleType*> getModules();

			template <class ModuleType>
			void attachModule(ModuleType* module);

			template <class ModuleType, typename... Args>
			ModuleType* attachModule(Args... parameters);

			template <class ModuleType>
			int detachModule(ModuleType* toRemove);

			int getId() { return m_id; }
			
			std::string getName() { return m_name; }
			void setName(const std::string& name) { m_name = name; }

			Transform* getTransform() { return m_transform; }
	};	
}