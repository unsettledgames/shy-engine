#pragma once
#include <string>
#include <vector>
#include <util/Classes.h>

namespace ShyEngine
{
	class Entity;

	/**
		\brief Modules hold the data used by Systems to update entities. Every System is tied to its type
			of module (e.g. the SpriteRenderer to the Sprite module, the PhysicsManager to the Physics module)
	*/
	class Module
	{
		friend class _ShyEngine;
		friend class System;
		friend class Entity;
		friend bool operator==(const Module& e1, const Module& e2);

		protected:
			// Self reference if I need to edit it externally (REFACTOR: remove?)
			Module* m_reference;
			// Identifier of the module
			int m_id;

		public:
			// Type of the module: it's a hash of its name
			static const std::size_t Type;
			// Name of the module
			static const std::string m_name;

			// Entity the MOdule is attached to
			Entity* m_entity;

			Module() {}
			Module(Entity* entity);
			~Module() {};

			bool operator==(Module* other);

			Entity* getEntity() { return m_entity; }

			/*
				\brief	Checks the compatibility of this Module given a list of modules that are already attached
						to a certain Entity. This is to avoid inconsistencies such as more than 1 Transform component
						or more than 1 Physics component etc. Derived class can implement the necessary version of
						checkCompatibility.

				\param	otherModules The modules that are already attached to the Entity we want to attach this
						Module to
				\return true if the module is compatible, false otherwise
			*/
			virtual bool checkCompatibility(std::vector<Module*>& otherModules) { return true; }

			/*
				\brief	Checks if this modules depends on the modules that are already attached to a certain 
						Entity. This is to avoid inconsistencies when detaching or destroying Modules (such as
						removing a Physics module while a Collider is still attached, or trying to remove the
						Transform component).

				\param	otherModules The modules that are already attached to the Entity 

				\return true if there are dependencies, false otherwise
			*/
			virtual bool checkDependency(std::vector<Module*>& otherModules) { return false; }

			/*
				\brief Tells whether or not the Module is of a certain type
			*/
			virtual bool IsClassType(const std::size_t classType) const { return classType == Type; }

			int getId() { return m_id; }
			Module* getReference() { return m_reference; }
	};
}