#pragma once

#include <engine/modules/collisions/Collider2D.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class RectCollider2D : public Collider2D
	{
		CLASS_DECLARATION(RectCollider2D);

		private:
			glm::vec2 m_rectSize;

		public:
			RectCollider2D(Entity* entity);
			RectCollider2D(Entity* entity, glm::vec2 size);

			void setSize(glm::vec2 size) { m_rectSize = size; }

			bool checkCompatibility(std::vector<Module*>& otherModules);
			bool checkDependency(std::vector<Module*>& otherModules);

			/*
				So
				Apparently each collider should have a copy of each other's colliding function:

				checkCollision(Collider)
					switch (colliderType)
						case Rect:
							do stuff
						case Circle:
							do other stuff

				Maybe the methods could stay in Collider2D? And the subclasses can call them: in this case the 
				colliders are merely containers of data and don't do much on their own
			*/
	};
}