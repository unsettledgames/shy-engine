#pragma once

#include <engine/modules/collisions/Collider2D.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class RectCollider2D : public Collider2D
	{
		friend class Collider2D;

		CLASS_DECLARATION(RectCollider2D);

		private:
			glm::vec2 m_rectSize;

		public:
			RectCollider2D(Entity* entity);
			RectCollider2D(Entity* entity, glm::vec2 size);

			void setSize(glm::vec2 size) { m_rectSize = size; }
			glm::vec2 getRectSize() { return m_rectSize; }

			glm::vec4 getRectBounds() { return glm::vec4(m_transform->getPos(), m_rectSize); }
	};
}