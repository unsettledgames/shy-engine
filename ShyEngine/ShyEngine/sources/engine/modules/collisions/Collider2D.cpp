#include <engine/modules/collisions/Collider2D.h>

namespace ShyEngine
{
	Collider2D::Collider2D() {}

	Collider2D::Collider2D(std::string&& name, Entity* entity) : Collider2D(name, entity) {}

	Collider2D::Collider2D(std::string& name, Entity* entity) : Module(name, entity) 
	{
		m_transform = entity->getTransform();
	}

	Collider2D::Collider2D(Entity* entity) : Collider2D("Collider2D", entity) {}

	bool Collider2D::checkCollision(std::vector<Collider2D*> colliders)
	{
		bool ret = false;

		for (auto collider : colliders)
			ret = ret || checkCollision(collider);
		
		return ret;
	}

	bool Collider2D::checkCollisionOptimized(std::vector<Collider2D*> colliders)
	{
		for (auto collider : colliders)
		{
			if (checkCollision(collider))
				return true;
		}

		return false;
	}

	bool Collider2D::checkCollision(Transform* other)
	{
		return checkCollision(glm::vec4(other->getPos(), other->getScale()));
	}

	bool Collider2D::checkCollision(Collider2D* other)
	{
		return checkCollision(glm::vec4(other->m_transform->getPos(), other->m_transform->getScale()));
	}

	bool Collider2D::checkCollision(glm::vec4 rect)
	{
		return AABB(glm::vec4(m_transform->getPos(), m_transform->getScale()), rect);
	}

	bool Collider2D::AABB(glm::vec4 first, glm::vec4 second)
	{
		glm::vec2 thisPos = glm::vec2(first.x, first.y);
		glm::vec2 thisScale = glm::vec2(first.z, first.w);
		glm::vec2 minDistance = (thisScale + glm::vec2(second.z, second.w)) / 2.0f;

		glm::vec2 distance = thisPos - glm::vec2(second.x, second.y);
		glm::vec2 depth = minDistance - glm::abs(distance);

		return depth.x > 0 && depth.y > 0;
	}

	bool Collider2D::checkCompatibility(std::vector<Module>& otherModules) 
	{
		// There must exist a Transform component
		return std::find_if(otherModules.begin(), otherModules.end(),
			[](Module other) { return other.getName() == "Transform"; }) != otherModules.end();
	}

	bool Collider2D::checkDependency(std::vector<Module>& otherModules) 
	{ 
		return false; 
	}
}