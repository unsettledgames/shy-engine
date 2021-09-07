#include <engine/systems/PhysicsManager.h>
#include <engine/modules/Physics.h>

namespace ShyEngine
{
	PhysicsManager::PhysicsManager() : System("PhysicsManager") 
	{
		m_gravity = glm::vec2(0.0f, -9.81f);
	}

	void PhysicsManager::init() {}

	void PhysicsManager::updateModules(PhysicsData data)
	{
		for (Module* m : m_modulesPointers)
			((Physics*)m)->update(data);
	}
}