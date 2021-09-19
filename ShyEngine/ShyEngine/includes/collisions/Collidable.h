#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <engine/Entity.h>
#include <engine/Module.h>
#include <util/Classes.h>

#include <collisions/CollisionGrid.h>
#include <engine/modules/collisions/Collider2D.h>

/*
* COLLISION SYSTEM:
* 
* - An object may have a collider
* - Colliders are able to detect collisions via the collision manager, which handles the colliders to pass to each
*		collider to check against via spatial partitioning
* - When a collider detects a collision, it checks all the modules of an object to see if they contain a Collidable
*		object. If an object is Collidable, then the collision functions are called at the right moments.
*/

namespace ShyEngine
{
	class CollisionManager;

	class Collidable : public Module
	{
		CLASS_DECLARATION(Collidable);

		friend class CollisionManager;

		private:
			bool m_prevContact = false;
			glm::vec2 m_cellCoords = glm::vec2(0, 0);
			
			CollisionGrid* m_collisionGrid;
			Collider2D* m_currentCollider;

		public:
			Collidable();
			Collidable(Entity* entity) : Module(entity) {}
			~Collidable();

			void handleCollision(bool contact, Collider2D* collidedCollider);

			virtual void onCollisionStarted(Collider2D* collider) {};
			virtual void onCollisionFinished(Collider2D* collider) {};
			virtual void onCollisionStay(Collider2D* collider) {};
	};
}