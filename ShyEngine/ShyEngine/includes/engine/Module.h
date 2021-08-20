#pragma once
#include <string>
#include <vector>

namespace ShyEngine
{
	class Entity;

	enum class ModuleTypes
	{
		Transform,
		Physics,
		Collider,
		Camera,
		Sprite
	};

	class Module
	{
		friend class ShyEngine;
		friend class System;
		friend class Entity;
		friend bool operator==(const Module& e1, const Module& e2);

		protected:
			Module* m_reference;
			Entity* m_entity;
			std::string m_name;
			int m_id;

		public:
			Module(const std::string& name) { m_name = name; };
			~Module() {};

			bool operator==(Module* other);

			const std::string getName() { return m_name; }
			Entity* getEntity() { return m_entity; }

			virtual bool checkCompatibility(std::vector<Module>& otherModules) { return true; }
			virtual bool checkDependency(std::vector<Module>& otherModules) { return true; }

			int getId() { return m_id; }
	};
}