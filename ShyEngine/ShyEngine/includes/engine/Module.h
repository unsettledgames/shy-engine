#pragma once
#include <string>
#include <vector>
#include <util/Classes.h>

namespace ShyEngine
{
	enum class ModuleTypes
	{
		Transform,
		Physics,
		Collider,
		Camera,
		Sprite
	};

	class Entity;

	class Module
	{
		friend class ShyEngine;
		friend class System;
		friend class Entity;
		friend bool operator==(const Module& e1, const Module& e2);

		protected:
			Module* m_reference;
			Entity* m_entity;
			int m_id;

		public:
			static const std::size_t Type;
			static const std::string m_name;

			Module() {}
			Module(Entity* entity);
			~Module() {};

			bool operator==(Module* other);

			Entity* getEntity() { return m_entity; }

			virtual bool checkCompatibility(std::vector<Module>& otherModules) { return true; }
			virtual bool checkDependency(std::vector<Module>& otherModules) { return true; }
			virtual bool IsClassType(const std::size_t classType) const { return classType == Type; }

			int getId() { return m_id; }
			Module* getReference() { return m_reference; }
	};
}