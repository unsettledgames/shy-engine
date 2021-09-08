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

			std::vector<Collidable*> getCollidables();

			template <class ModuleType, typename... Args>
			void attachModule(ModuleType* module);

			template <class ModuleType, typename... Args>
			ModuleType* attachModule(Args... parameters);

			template <class ModuleType>
			int detachModule(ModuleType toRemove);

			template <class ModuleType>
			void detachModules(std::vector<ModuleType*> toRemove);

			int getId() { return m_id; }
			
			std::string getName() { return m_name; }
			void setName(const std::string& name) { m_name = name; }

			Transform* getTransform() { return m_transform; }
	};	
}

/*

//***************
    // GameObject::AddComponent
    // perfect-forwards all params to the ComponentType constructor with the matching parameter list
    // DEBUG: be sure to compare the arguments of this fn to the desired constructor to avoid perfect-forwarding failure cases
    // EG: deduced initializer lists, decl-only static const int members, 0|NULL instead of nullptr, overloaded fn names, and bitfields
    //***************
    template< class ComponentType, typename... Args >
    void GameObject::AddComponent(Args&&... params) {
        components.emplace_back(std::make_unique< ComponentType >(std::forward< Args >(params)...));
    }

    //***************
    // GameObject::GetComponent
    // returns the first component that matches the template type
    // or that is derived from the template type
    // EG: if the template type is Component, and components[0] type is BoxCollider
    // then components[0] will be returned because it derives from Component
    //***************
    template< class ComponentType >
    ComponentType& GameObject::GetComponent() {
        for (auto&& component : components) {
            if (component->IsClassType(ComponentType::Type))
                return *static_cast<ComponentType*>(component.get());
        }

        return *std::unique_ptr< ComponentType >(nullptr);
    }

    //***************
    // GameObject::RemoveComponent
    // returns true on successful removal
    // returns false if components is empty, or no such component exists
    //***************
    template< class ComponentType >
    bool GameObject::RemoveComponent() {
        if (components.empty())
            return false;

        auto& index = std::find_if(components.begin(),
            components.end(),
            [classType = ComponentType::Type](auto& component) {
            return component->IsClassType(classType);
        });

        bool success = index != components.end();

        if (success)
            components.erase(index);

        return success;
    }


*/