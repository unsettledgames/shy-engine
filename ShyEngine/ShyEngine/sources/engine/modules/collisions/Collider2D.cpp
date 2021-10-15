#include <engine/modules/collisions/Collider2D.h>
#include <engine/modules/Physics.h>
#include <engine/modules/collisions/CircleCollider2D.h>
#include <engine/modules/collisions/RectCollider2D.h>

namespace ShyEngine
{	
	CLASS_DEFINITION(Module, Collider2D);

	Collider2D::Collider2D() : Module(nullptr){}

	Collider2D::Collider2D(Entity* entity) : Module(entity) 
	{
		m_transform = entity->getTransform();
	}

	// OPTIMIZABLE: make AABB a macro instead of a function
	// OPTIMIZABLE: make as many members as possible public to remove calls
	bool Collider2D::checkCollision(glm::vec4 rect)
	{
		return AABB(glm::vec4(m_transform->getPos(), m_transform->getScale()), rect);
	}

	bool Collider2D::AABB(glm::vec4 first, glm::vec4 second)
	{
		// Scale of the first one + scale of the second one / 2
		glm::vec2 minDistance = (glm::vec2(first.z, first.w) + glm::vec2(second.z, second.w)) / 2.0f;
		// First position - second position
		glm::vec2 distance = glm::abs(glm::vec2(first.x, first.y) - glm::vec2(second.x, second.y));
		glm::vec2 tempDepth = minDistance - distance;

		return (tempDepth.x > 0 && tempDepth.y > 0);
	}

	bool Collider2D::checkCompatibility(std::vector<Module*>& otherModules) 
	{
		// There must exist a Physics component
		return std::find_if(otherModules.begin(), otherModules.end(),
			[](Module* other) { return other->IsClassType(Physics::Type); }) != otherModules.end();
	}

	bool Collider2D::checkDependency(std::vector<Module*>& otherModules) 
	{
		// Nothing depends on the collider
		return false; 
	}
}