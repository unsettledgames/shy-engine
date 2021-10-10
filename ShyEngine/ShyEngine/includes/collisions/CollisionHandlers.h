#pragma once

#include <data/SystemData.h>

#include <engine/modules/collisions/CircleCollider2D.h>
#include <engine/modules/collisions/RectCollider2D.h>

/*
	This files contains the functions used to handle the collisions. They're defined here to avoid circular dependencies
	(eg circleVsRect defined in CircleCollider, but the Collider2D has to include it and then Collider2D->CircleCollider
	and CircleCollider->Collider2D) and repetitions (there's no need to have both circleVsRect and rectVsCircle).
*/

namespace ShyEngine
{
	/*
		\brief	Checks whether a CircleCollider2D is colliding with a RectCollider2D

		At the moment, the engine performs a simple AABB check.

		\param circle	The abovementioned CircleCollider2D
		\param rect	The abovementioned RectCollider2D

		\return	An object containing the data regarding the collision
	*/
	CollisionData circleVsRect(CircleCollider2D* circle, RectCollider2D* rect);

	/*
		\brief	Checks whether a RectCollider2D is colliding with another RectCollider2D

		At the moment this function is unimplemented.

		\param rect	The first RectCollider2D
		\param rect	The second RectCollider2D

		\return	An object containing the data regarding the collision
	*/
	CollisionData rectVsRect(RectCollider2D* first, RectCollider2D* second);

	/*
		\brief	Checks whether a CircleCollider2D is colliding with another CircleCollider2D

		This functions checks whether or not the distance between the two colliders is less than the sum 
		of their radii.

		\param rect	The first CircleCollider2D
		\param rect	The second CircleCollider2D

		\return	An object containing the data regarding the collision
	*/
	CollisionData circleVsCircle(CircleCollider2D* first, CircleCollider2D* second);

	/*
		\brief	Checks whether a Collider2D is colliding with another Collider2D

		This functions acts as a dispatcher and calls the right function depending on the type of the 
		two colliders.

		\param rect	The first Collider2D
		\param rect	The second Collider2D

		\return	An object containing the data regarding the collision
	*/
	CollisionData checkCollision(Collider2D* first, Collider2D* second);
}