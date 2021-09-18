#pragma once

#include <vector>

#include <engine/Module.h>
#include <engine/modules/Transform.h>
#include <engine/Entity.h>
#include <util/Classes.h>

namespace ShyEngine
{
	class Collider2D : public Module
	{
		CLASS_DECLARATION(Collider2D);

		class CollisionManager;
		friend class CollisionManager;

		protected:
			bool m_auto = false;

			std::vector<Entity> m_collisionEntities;
			Transform* m_transform;

		public:
			Collider2D();
			Collider2D(Entity* entity);
			~Collider2D() {}

			bool checkCollision(std::vector<Collider2D*> colliders);
			bool checkCollisionOptimized(std::vector<Collider2D*> colliders);

			bool checkCollision(Collider2D* otherCollider);
			bool checkCollision(Transform* otherTransform);
			bool checkCollision(glm::vec4 otherRect);

			bool checkCompatibility(std::vector<Module*>& otherModules);
			bool checkDependency(std::vector<Module*>& otherModules);

			static bool AABB(glm::vec4 first, glm::vec4 second);
	};
}