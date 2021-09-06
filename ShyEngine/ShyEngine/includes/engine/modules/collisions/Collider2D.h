#pragma once

#include <vector>

#include <engine/Module.h>
#include <engine/modules/Transform.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	class Collider2D : public Module
	{
		class CollisionManager;
		friend class CollisionManager;

		protected:
			bool m_auto = false;

			std::vector<Entity> m_collisionEntities;
			Transform* m_transform;

		public:
			Collider2D();
			~Collider2D() {}

			bool checkCollision(Collider2D* otherCollider);
			bool checkCollision(Transform* otherTransform);
			bool checkCollision(glm::vec4 otherRect);

			bool checkCompatibility(std::vector<Module>& otherModules);
			bool checkDependency(std::vector<Module>& otherModules);

			static bool AABB(glm::vec4 first, glm::vec4 second);
	};
}