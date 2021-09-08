#pragma once

#include <engine/Entity.h>
#include <engine/Module.h>

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
	class Collidable : public Module
	{
		private:
			bool m_prevContact = false;
		public:
			Collidable();
			Collidable(Entity* entity) : Module(entity) {}
			~Collidable();

			void handleCollision(bool contact);

			void onCollisionStarted() {};
			void onCollisionFinished() {};
			void onCollisionStay() {};
	};
}