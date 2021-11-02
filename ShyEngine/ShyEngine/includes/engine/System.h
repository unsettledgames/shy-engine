#pragma once

#include <string>
#include <vector>

#include <engine/Module.h>

// REFACTOR: implement removeModule

namespace ShyEngine
{
	class Entity;

	/*
		\brief	Updates the data of a list of modules and implements a certain feature (such as Rendering or
				CollisionHandling). 
	*/
	class System
	{
		protected:
			// Pointers to the modules. We're storing pointers so that the data is correctly updated.
			// REFACTOR: this is inefficient as I'm not using caching. Should probably find another way or
			// put the Module values into m_modules at the beginning of each frame.
			std::vector<Module*> m_modulesPointers;
			// The actual modules
			std::vector<Module> m_modules;
			// Name of the system
			std::string m_name;

		public:
			System(const std::string& name) { m_name = name; }

			/*
				\brief Adds a module to the list of modules that the system should update
			*/
			void addModule(Module* toAdd);
			
			/*
				\brief Removes a module from the list of modules that the system should update
			*/
			int removeModule(Module* toRemove);
			
			/*
				\brief	Updates all the modules registered to this system.
			*/
			void updateModules() {};
	};
}