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
}