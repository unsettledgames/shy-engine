#include <engine/modules/collisions/RectCollider2D.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Collider2D, RectCollider2D);

	RectCollider2D::RectCollider2D(Entity* entity) : Collider2D(entity)
	{
		m_rectSize = m_transform->getScale();
	}

	RectCollider2D::RectCollider2D(Entity* entity, glm::vec2 size) : Collider2D(entity)
	{
		m_rectSize = size;
	}

	bool RectCollider2D::checkCompatibility(std::vector<Module*>& otherModules)
	{
		// There must exist a Transform component
		return std::find_if(otherModules.begin(), otherModules.end(),
			[](Module* other) { return other->Type == Transform::Type; }) != otherModules.end();
	}

	bool RectCollider2D::checkDependency(std::vector<Module*>& otherModules)
	{
		return false;
	}
}