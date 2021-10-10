#pragma once

#include <vector>

#include <engine/Module.h>
#include <data/SystemData.h>
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
		friend class Collider2D;

		protected:
			bool m_auto = false;

			std::vector<Entity> m_collisionEntities;
			Transform* m_transform;

		public:
			Collider2D();
			Collider2D(Entity* entity);
			~Collider2D() {}

			virtual CollisionData checkCollision(Collider2D* second) { return CollisionData::CollisionData(); };
			bool checkCollision(glm::vec4 otherRect);

			virtual bool checkCompatibility(std::vector<Module*>& otherModules);
			virtual bool checkDependency(std::vector<Module*>& otherModules);

			Transform* getTransform() { return m_transform; }

			static bool AABB(glm::vec4 first, glm::vec4 second);
	};
}