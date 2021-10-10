#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <engine/Entity.h>
#include <engine/Module.h>
#include <util/Classes.h>

#include <collisions/CollisionGrid.h>
#include <engine/modules/collisions/Collider2D.h>
#include <data/SystemData.h>

namespace ShyEngine
{
	class CollisionManager;

	/*
		\brief	Classes inheriting from Collidable are able to listen to collision events and handle them.

		Collidable derives from Module so that it's possible to define Modules that are able to intercept
		collision events by deriving from Collidable.

		An example of a built-in Collidable module is Physics, which needs to access the collision data of a body
		in order to simulate a realistic behaviour.

		The collision events are:

		- onCollisionStarted:	fired when a collision has started
		- onCollisionStay:		fired for each frame in which a collider causes a collision that had already started
		- onCollisionExit:		fired when a collision ends

		In all cases, a CollisionData object containing useful data about the collision that occurred, is passed
		to the function.
	*/
	class Collidable : public Module
	{
		CLASS_DECLARATION(Collidable);

		friend class CollisionManager;

		private:
			// Tells whether there was a contact in the previous frame
			bool m_prevContact = false;
			// The collider that caused a collision in the previous frame
			Collider2D* m_currentCollider;

			// UNUSED
			glm::vec2 m_cellCoords = glm::vec2(0, 0);
			// UNUSED
			CollisionGrid* m_collisionGrid;

		public:
			Collidable();
			Collidable(Entity* entity) : Module(entity) {}
			~Collidable();

			/*
				\brief	Calls the right collision event
				\param data	The data regarding the collision that occurred

				Basically handleCollision is a dispatcher that, depending on the state of the Collidable in the
				previous frame, decides which event should be called.
			*/
			void handleCollision(CollisionData data);

			/*
				\brief	Handles the event in which a collision starts
				\param data	The data about the collision
			*/
			virtual void onCollisionStarted(CollisionData data) {};

			/*
				\brief	Handles the event in which a collision finishes
				\param data	The data about the collision
			*/
			virtual void onCollisionFinished(CollisionData data) {};

			/*
				\brief	Handles the event in which a contact is kept across multiple frames
				\param data	The data about the collision
			*/
			virtual void onCollisionStay(CollisionData data) {};
	};
}