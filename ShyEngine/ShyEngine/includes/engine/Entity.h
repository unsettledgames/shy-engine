#pragma once

#include <string>
#include <vector>
#include <util/Error.h>
#include <algorithm>

#include <util/Classes.h>
#include <engine/modules/Transform.h>
#include <util/IdGenerator.h>

// REFACTOR: if registering a module to the entity's only purpose is to set the entity, why shouldn't this happen
//		in the module constructor?

namespace ShyEngine
{
	class Module;
	class Collidable;
	class CollisionManager;

	class Entity
	{
		friend class ShyEngine;
		friend class CollisionManager;

		protected:
			int m_id;

			std::string m_name;
			Entity* m_reference;

			// Vector containing all the modules that have been attached to this entity
			std::vector<Module*> m_modules;
			// Vector containing the modules that are collidable. This is to improve the perfomances of the CollisionManager
			std::vector<Collidable*> m_collidables;
			// Transform component: each Entity must have one
			Transform* m_transform;

		public:
			friend bool operator==(const Entity& e1, const Entity& e2);
			Entity(const std::string& name);
			~Entity() {}

			/*
				\brief	Returns the first module of type ModuleType that is found in the modules vector
				\return The first module of type ModuleType that is found
			*/
			template <class ModuleType>
			ModuleType* getModule()
			{
				for (Module* _module : this->m_modules)
					if (_module->IsClassType(ModuleType::Type))
						return dynamic_cast<ModuleType*>(_module);

				Error::runtime("Couldn't find module " + ModuleType::m_name + " on entity " + m_name);
				return nullptr;
			}

			/*
				\brief	Returns all the modules of type ModuleType attached to this entity
				\return A vector containing hte modules of type ModuleType attached to this entity
			*/
			template <class ModuleType>
			std::vector<ModuleType*> getModules()
			{
				std::vector<ModuleType*> ret;

				for (auto _module : m_modules)
					if (_module->IsClassType(ModuleType::Type))
						ret.push_back(dynamic_cast<ModuleType*>(_module));

				return ret;
			}

			/*
				\brief Attaches the module passed as an argument
				\param toAttach	Pointer to the module that should be attached to this entity
			*/
			template <class ModuleType>
			void attachModule(ModuleType* toAttach)
			{
				if (toAttach->checkCompatibility(m_modules))
				{
					m_modules.push_back(toAttach);

					if (toAttach->IsClassType(Collidable::Type))
						m_collidables.push_back((Collidable*)toAttach);
				}
				else
					Error::runtime("The module " + (toAttach->m_name) + " on the entity " + 
						toAttach->m_entity->getName() + " couldn't be added because it needs another component");
			}

			/*
				\brief Creates and attaches a module to this entity given the parameters of the constructor of
					that module
				\param parameters	The parameters of the constructor of the object with type ModuleType
				\return	The module that has been created
			*/
			template <class ModuleType, typename... Args>
			ModuleType* attachModule(Args... parameters)
			{
				ModuleType* ret = new ModuleType(parameters);

				if (ret->checkCompatibility(m_modules))
					m_modules.push_back(ret);

				return ret;
			}

			/*
				\brief	Detaches the module passed as an argument from this entity
				\param toRemove	The module that should be detached from this entity
				\return 0 if everything went right, -1 if the entity didn't have the module to remove,
					-2 if there was a dependency between a module and the one to detach
			*/
			template <class ModuleType>
			int detachModule(ModuleType* toRemove)
			{
				int error = 0;

				// If other modules don't depend on the module I want to remove
				if (toRemove->checkDependency(m_modules))
				{
					// Remove the module from the list, warn the user if it doesn't exist
					auto modIndex = std::find(m_modules.begin(), m_modules.end(), *toRemove);

					if (modIndex == m_modules.end())
					{
						Error::runtime("Couldn't find the module " + toRemove->getName() + " on the entity " + m_name +
							" while attempting to detach it");
						error = -1;
					}
					else
						m_modules.erase(modIndex);
				}
				else
					error = -2;

				return error;
			}

			int getId() { return m_id; }
			
			std::string getName() { return m_name; }
			void setName(const std::string& name) { m_name = name; }

			Transform* getTransform() { return m_transform; }
			std::vector<Collidable*> getCollidables() { return m_collidables; }
	};	
}